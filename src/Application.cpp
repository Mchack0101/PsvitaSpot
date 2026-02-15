#include "Application.h"
#include "Constants.h"

namespace PsvitaSpot {

Application::Application()
    : m_renderer(std::make_unique<Renderer>())
    , m_input(std::make_unique<InputHandler>())
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

    m_initialized = true;
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
    m_renderer->shutdown();
    m_initialized = false;
}

void Application::update() {
    m_input->update();

    if (m_input->shouldExit()) {
        m_running = false;
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

    m_renderer->endFrame();
}

}
