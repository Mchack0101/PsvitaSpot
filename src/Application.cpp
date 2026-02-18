#include "Application.h"
#include "Constants.h"

namespace PsvitaSpot {

Application::Application()
    : m_renderer(std::make_unique<Renderer>())
    , m_input(std::make_unique<InputHandler>())
    , m_spotifyAPI(std::make_shared<SpotifyAPI>())
    , m_spotifyUI(std::make_unique<SpotifyUI>())
    , m_playbackManager(std::make_unique<PlaybackManager>())
    , m_running(false)
    , m_initialized(false) {
}

Application::~Application() {
    shutdown();
}

bool Application::initialize() {
    if (m_initialized) {
        return true;
    }

    if (!m_renderer->initialize()) {
        return false;
    }

    if (!m_spotifyUI->initialize()) {
        return false;
    }

    initializeSpotify();

    m_initialized = true;
    return true;
}

bool Application::initializeSpotify() {
    std::string clientId = "";
    std::string clientSecret = "";
    std::string refreshToken = "";

    if (clientId.empty() || clientSecret.empty() || refreshToken.empty()) {
        return false;
    }

    if (!m_spotifyAPI->initialize(clientId, clientSecret, refreshToken)) {
        return false;
    }

    m_playbackManager->initialize(m_spotifyAPI);
    return true;
}

void Application::run() {
    if (!m_initialized) {
        return;
    }

    m_running = true;

    while (m_running) {
        update();
        render();
    }
}

void Application::shutdown() {
    if (!m_initialized) {
        return;
    }

    m_running = false;

    if (m_spotifyUI) {
        m_spotifyUI->shutdown();
    }

    if (m_renderer) {
        m_renderer->shutdown();
    }

    m_initialized = false;
}

void Application::update() {
    m_input->update();

    if (m_input->shouldExit()) {
        m_running = false;
        return;
    }

    if (m_playbackManager) {
        m_input->handleSpotifyControls(m_playbackManager.get());
        m_playbackManager->update();
    }
}

void Application::render() {
    m_renderer->beginFrame();

    m_renderer->clear(
        Config::CLEAR_COLOR_R,
        Config::CLEAR_COLOR_G,
        Config::CLEAR_COLOR_B,
        Config::CLEAR_COLOR_A
    );

    if (m_spotifyUI) {
        bool connected = m_playbackManager && m_playbackManager->isConnected();
        const PlaybackState& state = m_playbackManager
            ? m_playbackManager->getCurrentState()
            : PlaybackState{};

        m_spotifyUI->render(state, connected);
    }

    m_renderer->endFrame();
}

}
