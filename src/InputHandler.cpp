#include "InputHandler.h"
#include <cstring>

InputHandler::InputHandler() {
    memset(&currentPad, 0, sizeof(SceCtrlData));
    memset(&lastPad, 0, sizeof(SceCtrlData));
}

InputHandler::~InputHandler() {
    Shutdown();
}

void InputHandler::Initialize() {
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
}

void InputHandler::Update() {
    lastPad = currentPad;
    sceCtrlPeekBufferPositive(0, &currentPad, 1);
}

void InputHandler::Shutdown() {
}

bool InputHandler::IsButtonPressed(SceCtrlButtons button) const {
    return (currentPad.buttons & button) && !(lastPad.buttons & button);
}

bool InputHandler::IsButtonHeld(SceCtrlButtons button) const {
    return currentPad.buttons & button;
}

bool InputHandler::IsButtonReleased(SceCtrlButtons button) const {
    return !(currentPad.buttons & button) && (lastPad.buttons & button);
}

int InputHandler::GetLAnalogX() const {
    return currentPad.lx;
}

int InputHandler::GetLAnalogY() const {
    return currentPad.ly;
}

int InputHandler::GetRAnalogX() const {
    return currentPad.rx;
}

int InputHandler::GetRAnalogY() const {
    return currentPad.ry;
}
