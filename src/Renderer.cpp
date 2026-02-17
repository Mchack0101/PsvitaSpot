#include "Renderer.h"
#include "Constants.h"
#include <vitagl.h>

namespace PsvitaSpot {

Renderer::~Renderer() {
    shutdown();
}

bool Renderer::initialize() {
    if (m_initialized) {
        return true;
    }

    vglInitExtended(
        0,
        Config::SCREEN_WIDTH,
        Config::SCREEN_HEIGHT,
        Config::VGLMEM_SIZE,
        SCE_GXM_MULTISAMPLE_4X
    );

    m_initialized = true;
    return true;
}

void Renderer::shutdown() {
    if (m_initialized) {
        vglEnd();
        m_initialized = false;
    }
}

void Renderer::beginFrame() {
    if (!m_initialized) {
        return;
    }
    vglStartRendering();
}

void Renderer::endFrame() {
    if (!m_initialized) {
        return;
    }
    vglEndRendering();
    vglSwapBuffers(GL_FALSE);
}

void Renderer::clear(float r, float g, float b, float a) {
    if (!m_initialized) {
        return;
    }
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

}
