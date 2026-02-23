#pragma once
#include <string>

class SpotifyAPI {
public:
    SpotifyAPI(const std::string &token);
    std::string getCurrentTrack();
    void play();
    void pause();

private:
    std::string authToken;
};
