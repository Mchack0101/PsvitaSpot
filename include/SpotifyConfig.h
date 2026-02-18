#pragma once

#include <string>

namespace PsvitaSpot {
namespace Spotify {

struct Config {
    static constexpr const char* API_BASE_URL = "https://api.spotify.com/v1";
    static constexpr const char* AUTH_URL = "https://accounts.spotify.com/api/token";

    static constexpr int TOKEN_REFRESH_INTERVAL = 3000;
    static constexpr int POLL_INTERVAL = 1000;
};

struct Credentials {
    std::string clientId;
    std::string clientSecret;
    std::string refreshToken;
    std::string accessToken;
    long expiresAt = 0;
};

}
}
