#pragma once

#include "SpotifyConfig.h"
#include <string>
#include <memory>

namespace PsvitaSpot {

struct PlaybackState {
    std::string trackName;
    std::string artistName;
    std::string albumName;
    int progressMs = 0;
    int durationMs = 0;
    bool isPlaying = false;
    bool shuffle = false;
    int volume = 50;
};

class SpotifyAPI {
public:
    SpotifyAPI();
    ~SpotifyAPI();

    bool initialize(const std::string& clientId, const std::string& clientSecret, const std::string& refreshToken);
    bool refreshAccessToken();

    bool play();
    bool pause();
    bool next();
    bool previous();
    bool toggleShuffle();
    bool setVolume(int volume);

    bool getCurrentPlayback(PlaybackState& state);

    bool isAuthenticated() const { return !m_credentials.accessToken.empty(); }
    const PlaybackState& getLastPlaybackState() const { return m_lastState; }

private:
    std::string makeRequest(const std::string& endpoint, const std::string& method, const std::string& body = "");
    bool parsePlaybackResponse(const std::string& response, PlaybackState& state);
    long getCurrentTime() const;
    std::string extractJsonField(const std::string& json, const std::string& field) const;

    Spotify::Credentials m_credentials;
    PlaybackState m_lastState;
    bool m_initialized = false;
    void* m_netMemory = nullptr;  // Track allocated network memory for cleanup
};

}
