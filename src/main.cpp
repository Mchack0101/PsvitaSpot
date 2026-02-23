#include <vitaGL.h>
#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/sysmodule.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/http.h>
#include <cstdio>
#include <cstring>
#include "Renderer.h"
#include "SpotifyAPI.h"
#include "Constants.h"

int main() {
    // Load network & HTTP modules
    sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
    sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);

    // Initialize renderer
    Renderer renderer;
    renderer.Initialize();

    // Controller setup
    SceCtrlData pad;
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    // Spotify API (replace with your token)
    SpotifyAPI spotify("YOUR_SPOTIFY_OAUTH_TOKEN");

    bool running = true;
    while (running) {
        // Poll controller input
        sceCtrlPeekBufferPositive(0, &pad, 1);
        if (pad.buttons & SCE_CTRL_START) running = false;
        if (pad.buttons & SCE_CTRL_CROSS) spotify.play();
        if (pad.buttons & SCE_CTRL_CIRCLE) spotify.pause();
        if (pad.buttons & SCE_CTRL_TRIANGLE) spotify.nextTrack();
        if (pad.buttons & SCE_CTRL_SQUARE) spotify.previousTrack();

        // Clear screen
        renderer.Clear();

        // Fetch track info
        std::string track = spotify.getCurrentTrack();
        std::string artist = spotify.getCurrentArtist();
        float progress = spotify.getTrackProgress(); // 0.0 - 1.0

        // Draw text
        vglPrintConsole(10, 10, 0xFFFFFFFF, ("Track: " + track).c_str());
        vglPrintConsole(10, 30, 0xFFFFFFFF, ("Artist: " + artist).c_str());

        // Draw progress bar
        int barX = 10;
        int barY = 60;
        int barWidth = Constants::DISPLAY_WIDTH - 20;
        int barHeight = 10;

        // Background
        vglDrawRect(barX, barY, barWidth, barHeight, 0xFF444444);
        // Filled progress
        vglDrawRect(barX, barY, int(barWidth * progress), barHeight, 0xFF00FF00);

        // Swap buffers
        renderer.Present();

        // Wait 50ms
        sceKernelDelayThread(50000);
    }

    renderer.Shutdown();
    return 0;
}
