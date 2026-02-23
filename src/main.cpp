#include <vitaGL.h>
#include <psp2/ctrl.h>
#include <psp2/display.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/system_param.h>
#include <psp2/sysmodule.h>
#include <psp2/audioout.h>
#include <psp2/appmgr.h>
#include <psp2/touch.h>
#include <psp2/common_dialog.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/http.h>
#include <cstdio>
#include <cstring>
#include "Renderer.h"
#include "SpotifyAPI.h"
#include "Constants.h"

int main() {
    // Initialize Vita system modules
    sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
    sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);

    // Initialize display and renderer
    Renderer renderer;
    renderer.Initialize();

    // Initialize controller
    SceCtrlData pad;
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    // Replace with your actual Spotify OAuth token
    SpotifyAPI spotify("YOUR_SPOTIFY_OAUTH_TOKEN");

    bool running = true;
    while (running) {
        // Poll controller input
        sceCtrlPeekBufferPositive(0, &pad, 1);

        // Button actions
        if (pad.buttons & SCE_CTRL_START) {
            running = false; // Exit app
        }
        if (pad.buttons & SCE_CTRL_CROSS) {
            spotify.play();
        }
        if (pad.buttons & SCE_CTRL_CIRCLE) {
            spotify.pause();
        }

        // Clear screen
        renderer.Clear();

        // Simple text display (current track)
        std::string track = spotify.getCurrentTrack();
        vglPrintConsole(0, 0, 0xFFFFFFFF, track.c_str());

        // Swap buffers
        renderer.Present();

        // Sleep a bit
        sceKernelDelayThread(50000); // 50ms
    }

    // Shutdown
    renderer.Shutdown();
    return 0;
}
