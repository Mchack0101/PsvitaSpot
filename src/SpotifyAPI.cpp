#include "SpotifyAPI.h"

SpotifyAPI::SpotifyAPI(const std::string &token)
    : authToken(token), authenticated(!token.empty()) {}

std::string SpotifyAPI::getCurrentTrack() {
    return "No Track";
}

void SpotifyAPI::play() {
}

void SpotifyAPI::pause() {
}

void SpotifyAPI::next() {
}

void SpotifyAPI::previous() {
}

void SpotifyAPI::toggleShuffle() {
}

void SpotifyAPI::setVolume(int volume) {
}

bool SpotifyAPI::getCurrentPlayback(PlaybackState& state) {
    return false;
}

bool SpotifyAPI::isAuthenticated() const {
    return authenticated;
}
