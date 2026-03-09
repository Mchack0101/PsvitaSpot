#include "Renderer.h"
#include "Constants.h"
#include <vitaGL.h>
#include <psp2/gxm.h>

Renderer::Renderer() {}
Renderer::~Renderer() { Shutdown(); }

bool Renderer::Initialize() {
    vglInitExtended(0, Constants::VRAM_WIDTH, Constants::VRAM_HEIGHT,
        0x60000, SCE_GXM_MULTISAMPLE_NONE);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glViewport(0, 0, Constants::DISPLAY_WIDTH, Constants::DISPLAY_HEIGHT);
    return true;
}

void Renderer::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Present() {
    vglSwapBuffers(GL_FALSE);
}

void Renderer::Shutdown() {
    vglEnd();
    glFinish();
}

float Renderer::GetDisplayWidth() const {
    return static_cast<float>(Constants::DISPLAY_WIDTH);
}

float Renderer::GetDisplayHeight() const {
    return static_cast<float>(Constants::DISPLAY_HEIGHT);
}
