#include "PlaybackManager.h"

namespace PsvitaSpot {

PlaybackManager::PlaybackManager()
    : m_connected(false)
    , m_pollCounter(0) {
}

PlaybackManager::~PlaybackManager() {
}

bool PlaybackManager::initialize(std::shared_ptr<SpotifyAPI> api) {
    m_api = api;
    m_connected = api && api->isAuthenticated();
    return m_connected;
}

void PlaybackManager::update() {
    if (!m_api || !m_connected) {
        return;
    }

    m_pollCounter++;
    if (m_pollCounter >= POLL_RATE) {
        m_pollCounter = 0;
        updatePlaybackState();
    }
}

void PlaybackManager::updatePlaybackState() {
    if (m_api && m_api->getCurrentPlayback(m_currentState)) {
    }
}

void PlaybackManager::play() {
    if (m_api && m_connected) {
        m_api->play();
        m_currentState.isPlaying = true;
    }
}

void PlaybackManager::pause() {
    if (m_api && m_connected) {
        m_api->pause();
        m_currentState.isPlaying = false;
    }
}

void PlaybackManager::togglePlayPause() {
    if (m_currentState.isPlaying) {
        pause();
    } else {
        play();
    }
}

void PlaybackManager::next() {
    if (m_api && m_connected) {
        m_api->next();
    }
}

void PlaybackManager::previous() {
    if (m_api && m_connected) {
        m_api->previous();
    }
}

void PlaybackManager::toggleShuffle() {
    if (m_api && m_connected) {
        m_api->toggleShuffle();
        m_currentState.shuffle = !m_currentState.shuffle;
    }
}

void PlaybackManager::volumeUp() {
    if (m_api && m_connected) {
        int newVolume = m_currentState.volume + 5;
        if (newVolume > 100) newVolume = 100;
        m_api->setVolume(newVolume);
        m_currentState.volume = newVolume;
    }
}

void PlaybackManager::volumeDown() {
    if (m_api && m_connected) {
        int newVolume = m_currentState.volume - 5;
        if (newVolume < 0) newVolume = 0;
        m_api->setVolume(newVolume);
        m_currentState.volume = newVolume;
    }
}

}
