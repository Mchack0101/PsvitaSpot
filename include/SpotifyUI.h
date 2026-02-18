#pragma once

#include "SpotifyAPI.h"
#include <string>

namespace PsvitaSpot {

class SpotifyUI {
public:
    SpotifyUI();
    ~SpotifyUI();

    bool initialize();
    void shutdown();
    void render(const PlaybackState& state, bool connected);

private:
    void renderConnectedUI(const PlaybackState& state);
    void renderDisconnectedUI();
    void renderProgressBar(int current, int total, float x, float y, float width, float height);
    void renderText(const std::string& text, float x, float y, float size, float r, float g, float b);
    void renderButton(const std::string& label, float x, float y, float width, float height, bool highlight);
    std::string formatTime(int milliseconds) const;

    bool m_initialized = false;
};

}
