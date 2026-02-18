#pragma once

#include <vitasdk.h>

namespace PsvitaSpot {

class PlaybackManager;

class InputHandler {
public:
    InputHandler() = default;

    void update();
    void handleSpotifyControls(PlaybackManager* manager);

    bool isPressed(uint32_t button) const;
    bool isHeld(uint32_t button) const;
    bool isReleased(uint32_t button) const;

    bool shouldExit() const;

private:
    SceCtrlData m_currentPad = {};
    SceCtrlData m_previousPad = {};
};

}
