#include "SpotifyAPI.h"
#include "httplib.h"
#include "json.hpp"
using json = nlohmann::json;

SpotifyAPI::SpotifyAPI(const std::string &token)
    : authToken(token) {}

std::string SpotifyAPI::getCurrentTrack() {
    httplib::Client cli("https://api.spotify.com");
    httplib::Headers headers = {
        {"Authorization", "Bearer " + authToken}
    };
    auto res = cli.Get("/v1/me/player/currently-playing", headers);
    if (res && res->status == 200) {
        auto j = json::parse(res->body);
        return j["item"]["name"];
    }
    return "No Track";
}

void SpotifyAPI::play() {
    httplib::Client cli("https://api.spotify.com");
    httplib::Headers headers = {
        {"Authorization", "Bearer " + authToken}
    };
    cli.Put("/v1/me/player/play", headers, "", "application/json");
}

void SpotifyAPI::pause() {
    httplib::Client cli("https://api.spotify.com");
    httplib::Headers headers = {
        {"Authorization", "Bearer " + authToken}
    };
    cli.Put("/v1/me/player/pause", headers, "", "application/json");
}
