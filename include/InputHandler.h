#pragma once

#include <psp2/ctrl.h>

class InputHandler {
private:
    SceCtrlData currentPad;
    SceCtrlData lastPad;

public:
    InputHandler();
    ~InputHandler();
    
    void Initialize();
    void Update();
    void Shutdown();
    
    bool IsButtonPressed(SceCtrlButtons button) const;
    bool IsButtonHeld(SceCtrlButtons button) const;
    bool IsButtonReleased(SceCtrlButtons button) const;
    
    int GetLAnalogX() const;
    int GetLAnalogY() const;
    int GetRAnalogX() const;
    int GetRAnalogY() const;
};
