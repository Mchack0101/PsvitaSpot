#pragma once

#include "Renderer.h"
#include "InputHandler.h"
#include "SpotifyAPI.h"
#include "SpotifyUI.h"
#include "PlaybackManager.h"
#include <memory>

namespace PsvitaSpot {

class Application {
public:
    Application();
    ~Application();

    bool initialize();
    void run();
    void shutdown();

private:
    void update();
    void render();
    bool initializeSpotify();

    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<InputHandler> m_input;
    std::shared_ptr<SpotifyAPI> m_spotifyAPI;
    std::unique_ptr<SpotifyUI> m_spotifyUI;
    std::unique_ptr<PlaybackManager> m_playbackManager;
    bool m_running = false;
    bool m_initialized = false;
};

}
