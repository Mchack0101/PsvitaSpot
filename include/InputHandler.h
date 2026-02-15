#pragma once

#include <vitasdk.h>

namespace PsvitaSpot {

class InputHandler {
public:
    InputHandler() = default;

    void update();

    bool isPressed(uint32_t button) const;
    bool isHeld(uint32_t button) const;
    bool isReleased(uint32_t button) const;

    bool shouldExit() const;

private:
    SceCtrlData m_currentPad = {};
    SceCtrlData m_previousPad = {};
};

}
