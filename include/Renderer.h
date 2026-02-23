#pragma once

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    bool Initialize();
    void Clear();
    void Present();
    void Shutdown();
    
    float GetDisplayWidth() const;
    float GetDisplayHeight() const;
};
