#include "InputHandler.h"

namespace PsvitaSpot {

void InputHandler::update() {
    m_previousPad = m_currentPad;
    sceCtrlPeekBufferPositive(0, &m_currentPad, 1);
}

bool InputHandler::isPressed(uint32_t button) const {
    return (m_currentPad.buttons & button) && !(m_previousPad.buttons & button);
}

bool InputHandler::isHeld(uint32_t button) const {
    return (m_currentPad.buttons & button) != 0;
}

bool InputHandler::isReleased(uint32_t button) const {
    return !(m_currentPad.buttons & button) && (m_previousPad.buttons & button);
}

bool InputHandler::shouldExit() const {
    return isPressed(SCE_CTRL_START);
}

}
