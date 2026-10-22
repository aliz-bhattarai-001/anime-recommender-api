#pragma once
#include <string>
#include <vector>
// #include "../include/logging.hpp"

constexpr int DEFAULT_LIMIT = 10;
constexpr int MAX_LIMIT = 50;
constexpr float MAX_RATING = 10.0f;
constexpr int DEFAULT_MAX_EPISODES = 9999;

// Log logger;

enum AnimeType
{
    TV,
    Movie,
    OVA,
    Special,
    Unknowned
};

typedef struct
{
    std::string title;
    std::vector<std::string> genres;
    AnimeType type;
    int episodes;
    float rating;
} Anime;

typedef struct
{
    std::string genre;
    std::string type;
    float min_rating;
    int max_episodes;
    int limit;
} QueryParams;

typedef struct
{
    const Anime *ref;
    float score;
} ScoredAnime;
