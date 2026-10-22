#include "../include/recommender.hpp"
#include <algorithm>

// scoring logic is as simple as it can get here.
float Recommender::score(const Anime &a, const QueryParams &params)
{
    float accScore = 0.0f;

    if (Filter::matchGenre(a, params.genre))
        accScore += 2.0f;

    accScore += (a.rating / MAX_RATING) * 1.0f;

    if (params.max_episodes == 0)
    {
        if (a.episodes >= 12 && a.episodes <= 24)
            accScore += 0.5f;
    }
    else
    {
        if (Filter::matchEpisodesCount(a, params.max_episodes))
        {
            accScore += 0.5f;
        }
    }

    return accScore;
}

std::vector<ScoredAnime> Recommender::rank(const std::vector<const Anime *> &filtered, const QueryParams &params)
{
    std::vector<ScoredAnime> scoredAnimeList;

    // allocating enough room for all filtered elements initially.
    scoredAnimeList.reserve(filtered.size());

    for (const Anime *a : filtered)
    {
        if (a != nullptr)
        {
            float scoreVal = score(*a, params);
            scoredAnimeList.push_back({a, scoreVal});
        }
    }

    // sorting logic:
    auto sortingLogic = [](ScoredAnime &a, ScoredAnime &b)
    {
        return a.score > b.score;
    };

    std::sort(scoredAnimeList.begin(), scoredAnimeList.end(), sortingLogic);

    // Clamping the limit of scoredList to params.limit
    if (scoredAnimeList.size() > params.limit)
    {
        scoredAnimeList.resize(params.limit);
        // basically clears the excess data to be treated as inaccessible.
        // memory allocated remains but is now empty-like.
    }
    return scoredAnimeList;
}