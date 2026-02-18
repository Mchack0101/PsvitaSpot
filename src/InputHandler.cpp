#include "InputHandler.h"
#include "PlaybackManager.h"

namespace PsvitaSpot {

void InputHandler::update() {
    m_previousPad = m_currentPad;
    sceCtrlPeekBufferPositive(0, &m_currentPad, 1);
}

void InputHandler::handleSpotifyControls(PlaybackManager* manager) {
    if (!manager) {
        return;
    }

    if (isPressed(SCE_CTRL_CROSS)) {
        manager->togglePlayPause();
    }

    if (isPressed(SCE_CTRL_LTRIGGER)) {
        manager->previous();
    }

    if (isPressed(SCE_CTRL_RTRIGGER)) {
        manager->next();
    }

    if (isPressed(SCE_CTRL_SQUARE)) {
        manager->toggleShuffle();
    }

    if (isPressed(SCE_CTRL_UP)) {
        manager->volumeUp();
    }

    if (isPressed(SCE_CTRL_DOWN)) {
        manager->volumeDown();
    }
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
