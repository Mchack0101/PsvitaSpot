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
    if (m_netMemory) {
        free(m_netMemory);
        m_netMemory = nullptr;
    }
}

bool SpotifyAPI::initialize(const std::string& clientId, const std::string& clientSecret, const std::string& refreshToken) {
    if (m_initialized) return true;

    m_credentials.clientId = clientId;
    m_credentials.clientSecret = clientSecret;
    m_credentials.refreshToken = refreshToken;

    // Initialize network with proper memory management
    m_netMemory = malloc(1 * 1024 * 1024);
    if (!m_netMemory) return false;

    // Fix: use a proper variable instead of a temporary
    SceNetInitParam netParam;
    netParam.memory = m_netMemory;
    netParam.size   = 1 * 1024 * 1024;
    netParam.flags  = 0;

    int ret = sceNetInit(&netParam);
    if (ret < 0) {
        free(m_netMemory);
        m_netMemory = nullptr;
        return false;
    }

    sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);
    sceHttpInit(1 * 1024 * 1024);

    if (!refreshAccessToken()) return false;

    m_initialized = true;
    return true;
}

long SpotifyAPI::getCurrentTime() const {
    return sceKernelGetProcessTimeWide() / 1000000;
}

// ... rest of your SpotifyAPI.cpp code unchanged ...
