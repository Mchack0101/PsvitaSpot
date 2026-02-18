#include "SpotifyUI.h"
#include "Constants.h"
#include <vitagl.h>
#include <cstdio>
#include <cmath>

namespace PsvitaSpot {

SpotifyUI::SpotifyUI()
    : m_initialized(false) {
}

SpotifyUI::~SpotifyUI() {
    shutdown();
}

bool SpotifyUI::initialize() {
    if (m_initialized) {
        return true;
    }

    m_initialized = true;
    return true;
}

void SpotifyUI::shutdown() {
    m_initialized = false;
}

void SpotifyUI::render(const PlaybackState& state, bool connected) {
    if (!m_initialized) {
        return;
    }

    if (connected) {
        renderConnectedUI(state);
    } else {
        renderDisconnectedUI();
    }
}

void SpotifyUI::renderConnectedUI(const PlaybackState& state) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    float centerY = Config::SCREEN_HEIGHT / 2.0f;
    float albumArtY = centerY - 150;

    // Draw album art placeholder
    glColor4f(0.2f, 0.2f, 0.2f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(360, albumArtY);
        glVertex2f(600, albumArtY);
        glVertex2f(600, albumArtY + 240);
        glVertex2f(360, albumArtY + 240);
    glEnd();

    renderText("NOW PLAYING", 480 - 60, albumArtY - 40, 1.5f, 1.0f, 1.0f, 1.0f);

    // Track information
    renderText(state.trackName, 480 - (state.trackName.length() * 6), albumArtY + 260, 2.0f, 1.0f, 1.0f, 1.0f);
    renderText(state.artistName, 480 - (state.artistName.length() * 5), albumArtY + 290, 1.5f, 0.7f, 0.7f, 0.7f);
    renderText(state.albumName, 480 - (state.albumName.length() * 4), albumArtY + 315, 1.2f, 0.5f, 0.5f, 0.5f);

    // Progress bar
    float progressBarY = albumArtY + 360;
    renderProgressBar(state.progressMs, state.durationMs, 280, progressBarY, 400, 8);

    // Time display
    std::string timeStr = formatTime(state.progressMs) + " / " + formatTime(state.durationMs);
    renderText(timeStr, 480 - (timeStr.length() * 4), progressBarY + 20, 1.0f, 0.6f, 0.6f, 0.6f);

    // Control buttons
    float buttonY = progressBarY + 60;
    float buttonSpacing = 90;
    float startX = 240;

    renderButton("PREV", startX, buttonY, 80, 40, false);
    renderButton(state.isPlaying ? "PAUSE" : "PLAY", startX + buttonSpacing, buttonY, 80, 40, true);
    renderButton("NEXT", startX + buttonSpacing * 2, buttonY, 80, 40, false);
    renderButton(state.shuffle ? "SHFL ON" : "SHFL OFF", startX + buttonSpacing * 3, buttonY, 80, 40, state.shuffle);

    // Volume display
    std::string volumeStr = "Volume: " + std::to_string(state.volume) + "%";
    renderText(volumeStr, 480 - (volumeStr.length() * 4), buttonY + 60, 1.2f, 0.8f, 0.8f, 0.8f);

    // Control instructions
    renderText("Controls: X=Play/Pause | L/R=Prev/Next | Up/Down=Volume | Square=Shuffle",
               20, Config::SCREEN_HEIGHT - 40, 1.0f, 0.5f, 0.5f, 0.5f);
    renderText("START to exit", 20, Config::SCREEN_HEIGHT - 20, 1.0f, 0.5f, 0.5f, 0.5f);

    glDisable(GL_BLEND);
}

void SpotifyUI::renderDisconnectedUI() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float centerY = Config::SCREEN_HEIGHT / 2.0f;

    renderText("PsvitaSpot", 480 - 60, centerY - 100, 3.0f, 0.3f, 0.9f, 0.5f);
    renderText("Not connected to Spotify", 480 - 120, centerY, 1.5f, 0.8f, 0.2f, 0.2f);
    renderText("Configure credentials to connect", 480 - 140, centerY + 40, 1.2f, 0.6f, 0.6f, 0.6f);
    renderText("START to exit", 20, Config::SCREEN_HEIGHT - 20, 1.0f, 0.5f, 0.5f, 0.5f);
}

void SpotifyUI::renderProgressBar(int current, int total, float x, float y, float width, float height) {
    // Background bar
    glColor4f(0.3f, 0.3f, 0.3f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();

    // Progress fill
    if (total > 0) {
        float progress = static_cast<float>(current) / static_cast<float>(total);
        float progressWidth = width * progress;

        glColor4f(0.3f, 0.9f, 0.5f, 1.0f);
        glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + progressWidth, y);
            glVertex2f(x + progressWidth, y + height);
            glVertex2f(x, y + height);
        glEnd();
    }
}

void SpotifyUI::renderText(const std::string& text, float x, float y, float size, float r, float g, float b) {
    glColor4f(r, g, b, 1.0f);
    glRasterPos2f(x, y);
    
    // TODO: Implement actual text rendering with font support
    // This requires integrating a font rendering library such as:
    // - ImGui (recommended for PS Vita)
    // - Custom bitmap font renderer
    // - FreeType + custom rendering
    
    // Placeholder implementation sets up color and position
    // The actual text will not render without font support
}

void SpotifyUI::renderButton(const std::string& label, float x, float y, float width, float height, bool highlight) {
    // Button background
    if (highlight) {
        glColor4f(0.3f, 0.9f, 0.5f, 0.8f);
    } else {
        glColor4f(0.4f, 0.4f, 0.4f, 0.8f);
    }

    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();

    // Button border
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
    glEnd();

    // Button label
    renderText(label, x + 10, y + height / 2 + 5, 1.2f, 1.0f, 1.0f, 1.0f);
}

std::string SpotifyUI::formatTime(int milliseconds) const {
    int totalSeconds = milliseconds / 1000;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    char buffer[16];
    snprintf(buffer, sizeof(buffer), "%d:%02d", minutes, seconds);
    return std::string(buffer);
}

}
