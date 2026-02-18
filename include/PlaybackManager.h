#pragma once

#include "SpotifyAPI.h"
#include <memory>

namespace PsvitaSpot {

class PlaybackManager {
public:
    PlaybackManager();
    ~PlaybackManager();

    bool initialize(std::shared_ptr<SpotifyAPI> api);
    void update();

    void play();
    void pause();
    void togglePlayPause();
    void next();
    void previous();
    void toggleShuffle();
    void volumeUp();
    void volumeDown();

    const PlaybackState& getCurrentState() const { return m_currentState; }
    bool isConnected() const { return m_connected; }

private:
    void updatePlaybackState();

    std::shared_ptr<SpotifyAPI> m_api;
    PlaybackState m_currentState;
    bool m_connected = false;
    int m_pollCounter = 0;
    static constexpr int POLL_RATE = 60;
};

}
