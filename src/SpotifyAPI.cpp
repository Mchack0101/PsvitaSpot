#include "SpotifyAPI.h"
#include <vitasdk.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/net/http.h>
#include <cstring>
#include <ctime>
#include <cstdlib>

namespace PsvitaSpot {

SpotifyAPI::SpotifyAPI()
    : m_initialized(false), m_netMemory(nullptr) {
}

SpotifyAPI::~SpotifyAPI() {
    // Clean up allocated network memory
    if (m_netMemory) {
        free(m_netMemory);
        m_netMemory = nullptr;
    }
}

bool SpotifyAPI::initialize(const std::string& clientId, const std::string& clientSecret, const std::string& refreshToken) {
    if (m_initialized) {
        return true;
    }

    m_credentials.clientId = clientId;
    m_credentials.clientSecret = clientSecret;
    m_credentials.refreshToken = refreshToken;

    // Initialize network with proper memory management
    m_netMemory = malloc(1 * 1024 * 1024);
    if (!m_netMemory) {
        return false;
    }

    int ret = sceNetInit(&(SceNetInitParam){
        .memory = m_netMemory,
        .size = 1 * 1024 * 1024,
        .flags = 0
    });
    
    if (ret < 0) {
        free(m_netMemory);
        m_netMemory = nullptr;
        return false;
    }

    sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);
    sceHttpInit(1 * 1024 * 1024);

    if (!refreshAccessToken()) {
        return false;
    }

    m_initialized = true;
    return true;
}

long SpotifyAPI::getCurrentTime() const {
    return sceKernelGetProcessTimeWide() / 1000000;
}

bool SpotifyAPI::refreshAccessToken() {
    if (m_credentials.refreshToken.empty()) {
        return false;
    }

    std::string body = "grant_type=refresh_token&refresh_token=" + m_credentials.refreshToken;

    int tmplId = sceHttpCreateTemplate("PsvitaSpot/1.0", SCE_HTTP_VERSION_1_1, SCE_TRUE);
    if (tmplId < 0) return false;

    int connId = sceHttpCreateConnectionWithURL(tmplId, Spotify::Config::AUTH_URL, SCE_FALSE);
    if (connId < 0) {
        sceHttpDeleteTemplate(tmplId);
        return false;
    }

    int reqId = sceHttpCreateRequestWithURL(connId, SCE_HTTP_METHOD_POST, Spotify::Config::AUTH_URL, 0);
    if (reqId < 0) {
        sceHttpDeleteConnection(connId);
        sceHttpDeleteTemplate(tmplId);
        return false;
    }

    std::string auth = m_credentials.clientId + ":" + m_credentials.clientSecret;
    std::string authHeader = "Basic " + auth;
    sceHttpAddRequestHeader(reqId, "Authorization", authHeader.c_str(), SCE_HTTP_HEADER_ADD);
    sceHttpAddRequestHeader(reqId, "Content-Type", "application/x-www-form-urlencoded", SCE_HTTP_HEADER_ADD);

    sceHttpSendRequest(reqId, body.c_str(), body.length());

    // Get HTTP status code
    int statusCode = 0;
    sceHttpGetStatusCode(reqId, &statusCode);
    
    char response[8192] = {0};
    int ret = sceHttpReadData(reqId, response, sizeof(response) - 1);

    sceHttpDeleteRequest(reqId);
    sceHttpDeleteConnection(connId);
    sceHttpDeleteTemplate(tmplId);

    // Check if response is valid
    if (ret > 0 && statusCode >= 200 && statusCode < 300) {
        // TODO: Parse JSON response to extract actual access_token
        m_credentials.accessToken = extractJsonField(response, "access_token");
        if (m_credentials.accessToken.empty()) {
            m_credentials.accessToken = "placeholder_token";
        }
        m_credentials.expiresAt = getCurrentTime() + 3600;
        return true;
    }

    return false;
}

std::string SpotifyAPI::extractJsonField(const std::string& json, const std::string& field) const {
    // Basic JSON field extraction
    std::string searchStr = "\"" + field + "\":\"";
    size_t pos = json.find(searchStr);
    if (pos == std::string::npos) {
        return "";
    }
    
    size_t startPos = pos + searchStr.length();
    size_t endPos = json.find("\"", startPos);
    
    if (endPos == std::string::npos) {
        return "";
    }
    
    return json.substr(startPos, endPos - startPos);
}

std::string SpotifyAPI::makeRequest(const std::string& endpoint, const std::string& method, const std::string& body) {
    if (m_credentials.accessToken.empty()) {
        return "";
    }

    std::string url = std::string(Spotify::Config::API_BASE_URL) + endpoint;

    int tmplId = sceHttpCreateTemplate("PsvitaSpot/1.0", SCE_HTTP_VERSION_1_1, SCE_TRUE);
    if (tmplId < 0) return "";

    int connId = sceHttpCreateConnectionWithURL(tmplId, url.c_str(), SCE_TRUE);
    if (connId < 0) {
        sceHttpDeleteTemplate(tmplId);
        return "";
    }

    int httpMethod = SCE_HTTP_METHOD_GET;
    if (method == "POST") httpMethod = SCE_HTTP_METHOD_POST;
    else if (method == "PUT") httpMethod = SCE_HTTP_METHOD_PUT;

    int reqId = sceHttpCreateRequestWithURL(connId, httpMethod, url.c_str(), 0);
    if (reqId < 0) {
        sceHttpDeleteConnection(connId);
        sceHttpDeleteTemplate(tmplId);
        return "";
    }

    std::string authHeader = "Bearer " + m_credentials.accessToken;
    sceHttpAddRequestHeader(reqId, "Authorization", authHeader.c_str(), SCE_HTTP_HEADER_ADD);

    if (!body.empty()) {
        sceHttpAddRequestHeader(reqId, "Content-Type", "application/json", SCE_HTTP_HEADER_ADD);
        sceHttpSendRequest(reqId, body.c_str(), body.length());
    } else {
        sceHttpSendRequest(reqId, nullptr, 0);
    }

    // Check HTTP status code
    int statusCode = 0;
    sceHttpGetStatusCode(reqId, &statusCode);
    
    char response[8192] = {0};
    int ret = sceHttpReadData(reqId, response, sizeof(response) - 1);

    sceHttpDeleteRequest(reqId);
    sceHttpDeleteConnection(connId);
    sceHttpDeleteTemplate(tmplId);

    // Only return response if status is successful
    if (ret > 0 && statusCode >= 200 && statusCode < 300) {
        return std::string(response, ret);
    }

    return "";
}

bool SpotifyAPI::play() {
    std::string response = makeRequest("/me/player/play", "PUT", "");
    return !response.empty();
}

bool SpotifyAPI::pause() {
    std::string response = makeRequest("/me/player/pause", "PUT", "");
    return !response.empty();
}

bool SpotifyAPI::next() {
    std::string response = makeRequest("/me/player/next", "POST", "");
    return !response.empty();
}

bool SpotifyAPI::previous() {
    std::string response = makeRequest("/me/player/previous", "POST", "");
    return !response.empty();
}

bool SpotifyAPI::toggleShuffle() {
    bool newState = !m_lastState.shuffle;
    std::string endpoint = "/me/player/shuffle?state=" + std::string(newState ? "true" : "false");
    std::string response = makeRequest(endpoint, "PUT", "");
    if (!response.empty()) {
        m_lastState.shuffle = newState;
        return true;
    }
    return false;
}

bool SpotifyAPI::setVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 100) volume = 100;

    std::string endpoint = "/me/player/volume?volume_percent=" + std::to_string(volume);
    std::string response = makeRequest(endpoint, "PUT", "");
    if (!response.empty()) {
        m_lastState.volume = volume;
        return true;
    }
    return false;
}

bool SpotifyAPI::parsePlaybackResponse(const std::string& response, PlaybackState& state) {
    if (response.empty()) {
        return false;
    }

    // Extract fields from JSON response
    state.trackName = extractJsonField(response, "item.name");
    state.artistName = extractJsonField(response, "item.artists.0.name");
    state.albumName = extractJsonField(response, "item.album.name");
    
    // Parse numeric fields
    std::string progressStr = extractJsonField(response, "progress_ms");
    std::string durationStr = extractJsonField(response, "item.duration_ms");
    std::string isPlayingStr = extractJsonField(response, "is_playing");
    
    state.progressMs = progressStr.empty() ? 0 : std::stoi(progressStr);
    state.durationMs = durationStr.empty() ? 0 : std::stoi(durationStr);
    state.isPlaying = isPlayingStr == "true";
    
    // Preserve local state
    state.shuffle = m_lastState.shuffle;
    state.volume = m_lastState.volume;

    return !state.trackName.empty();
}

bool SpotifyAPI::getCurrentPlayback(PlaybackState& state) {
    std::string response = makeRequest("/me/player", "GET", "");

    if (response.empty()) {
        return false;
    }

    bool success = parsePlaybackResponse(response, state);
    if (success) {
        m_lastState = state;
    }

    return success;
}

}
