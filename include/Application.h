#pragma once

#include "Renderer.h"
#include "InputHandler.h"
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

    std::unique_ptr<Renderer> m_renderer;
    std::unique_ptr<InputHandler> m_input;
    bool m_running = false;
    bool m_initialized = false;
};

}
