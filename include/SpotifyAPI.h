#pragma once
#include <string>

struct PlaybackState {
    std::string trackName;
    std::string artistName;
    std::string albumName;
    int progressMs = 0;
    int durationMs = 0;
    bool isPlaying = false;
    bool shuffle = false;
    int volume = 50;
};

class SpotifyAPI {
public:
    SpotifyAPI(const std::string &token);
    std::string getCurrentTrack();
    void play();
    void pause();
    void next();
    void previous();
    void toggleShuffle();
    void setVolume(int volume);
    bool getCurrentPlayback(PlaybackState& state);
    bool isAuthenticated() const;

private:
    std::string authToken;
    bool authenticated = false;
};
