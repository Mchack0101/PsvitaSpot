#pragma once

namespace PsvitaSpot {

class Renderer {
public:
    Renderer() = default;
    ~Renderer();

    bool initialize();
    void shutdown();

    void beginFrame();
    void endFrame();
    void clear(float r, float g, float b, float a);

    bool isInitialized() const { return m_initialized; }

private:
    bool m_initialized = false;
};

}
