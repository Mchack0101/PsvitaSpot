#pragma once

class Renderer;
class InputHandler;

class Application {
private:
    Renderer* renderer;
    InputHandler* inputHandler;
    bool running;

public:
    Application();
    ~Application();
    
    bool Initialize();
    void Run();
    void Shutdown();
    bool IsRunning() const;
    
private:
    void Update();
    void Render();
};
