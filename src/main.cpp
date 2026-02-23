#include <vitaGL.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <stdio.h>
#include <string.h>

#include "Renderer.h"

#define TOKEN_PATH "ux0:data/PsvitaSpot/token.dat"

Renderer renderer;

/* ===============================
   TOKEN SAVE / LOAD FUNCTIONS
   =============================== */

void saveRefreshToken(const char* token) {
    // create folder if missing
    sceIoMkdir("ux0:data/PsvitaSpot", 0777);

    SceUID fd = sceIoOpen(
        TOKEN_PATH,
        SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC,
        0777
    );

    if (fd >= 0) {
        sceIoWrite(fd, token, strlen(token));
        sceIoClose(fd);
        printf("Refresh token saved.\n");
    }
}

bool loadRefreshToken(char* buffer, size_t size) {
    SceUID fd = sceIoOpen(TOKEN_PATH, SCE_O_RDONLY, 0777);

    if (fd < 0)
        return false;

    int read = sceIoRead(fd, buffer, size - 1);
    sceIoClose(fd);

    if (read <= 0)
        return false;

    buffer[read] = '\0';
    return true;
}

/* ===============================
   SPOTIFY LOGIN PLACEHOLDERS
   (you already have similar logic)
   =============================== */

void startSpotifyOAuthLogin() {
    printf("Opening Spotify login...\n");

    // TODO:
    // your existing OAuth browser/device login code goes here
    // once login succeeds you must call:
    //
    // saveRefreshToken(received_refresh_token);
}

void spotifyLoginWithRefreshToken(const char* refreshToken) {
    printf("Auto logging using saved refresh token...\n");

    // TODO:
    // your API request:
    // POST https://accounts.spotify.com/api/token
    // grant_type=refresh_token
    // refresh_token=<token>
}

/* ===============================
   MAIN APP LOOP
   =============================== */

int main() {

    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

    renderer.Initialize();

    char refreshToken[512];

    // ---- AUTO LOGIN CHECK ----
    if (loadRefreshToken(refreshToken, sizeof(refreshToken))) {
        printf("Saved token found.\n");
        spotifyLoginWithRefreshToken(refreshToken);
    } else {
        printf("No saved token.\n");
        startSpotifyOAuthLogin();
    }

    // ---- BASIC LOOP ----
    while (1) {

        SceCtrlData pad;
        sceCtrlPeekBufferPositive(0, &pad, 1);

        // Press START to exit
        if (pad.buttons & SCE_CTRL_START)
            break;

        renderer.Clear();
        renderer.Present();
    }

    renderer.Shutdown();
    sceKernelExitProcess(0);
    return 0;
}
