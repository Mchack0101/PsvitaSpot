#include "Application.h"
#include "Renderer.h"
#include "InputHandler.h"

Application::Application() : renderer(nullptr), inputHandler(nullptr), running(true) {}

Application::~Application() {
    Shutdown();
}

bool Application::Initialize() {
    renderer = new Renderer();
    if (!renderer->Initialize()) {
        return false;
    }
    
    inputHandler = new InputHandler();
    inputHandler->Initialize();
    
    return true;
}

void Application::Run() {
    while (running && IsRunning()) {
        Update();
        Render();
    }
}

void Application::Update() {
    inputHandler->Update();
    
    if (inputHandler->IsButtonPressed(SCE_CTRL_START)) {
        running = false;
    }
}

void Application::Render() {
    renderer->Clear();
    renderer->Present();
}

void Application::Shutdown() {
    if (inputHandler) {
        inputHandler->Shutdown();
        delete inputHandler;
        inputHandler = nullptr;
    }
    
    if (renderer) {
        renderer->Shutdown();
        delete renderer;
        renderer = nullptr;
    }
}

bool Application::IsRunning() const {
    return running;
}
