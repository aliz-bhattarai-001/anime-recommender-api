#pragma once
#include "../include/anime.h"

namespace Filter
{

    bool matchGenre(const Anime &a, const std::string &genre);
    bool matchType(const Anime &a, const std::string &type);
    bool matchRating(const Anime &a, float min_rating);
    bool matchEpisodesCount(const Anime &a, int max_episodes);
    std::vector<const Anime *> apply(const std::vector<Anime> &src, const QueryParams &params);
};