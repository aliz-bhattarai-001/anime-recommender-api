#include <iostream>
#include "../include/logging.hpp"
#include "../include/anime.h"
#include "../include/dataloader.hpp"
#include "../include/filter.hpp"

Log messageLogger;
bool Filter::matchGenre(const Anime &a, const std::string &genre)
{
    if (genre.empty())
        return true;

    for (auto each : a.genres)
    {
        if (each == Helpers::trim(Helpers::toLower(genre)))
            return true;
    }
    return false;
}

bool Filter::matchType(const Anime &a, const std::string &type)
{
    using namespace Helpers;
    if (type.empty())
        return true;

    AnimeType parsedType = DataLoader::parseType(trim(toLower(type)));
    if (a.type == parsedType)
        return true;

    return false;
}

bool Filter::matchRating(const Anime &a, float min_rating)
{
    if (min_rating == 0.0f)
        return true;

    return a.rating >= min_rating;
}

bool Filter::matchEpisodesCount(const Anime &a, int max_episodes)
{
    if (!max_episodes)
        return true;
    return a.episodes <= max_episodes;
}

std::vector<const Anime *> Filter::apply(const std::vector<Anime> &src, const QueryParams &params)
{
    std::vector<const Anime *> filteredList;
    int count = 0;
    // &each prevents copying and uses the actual object
    // : preventing dangling pointers in filteredlist vector.
    for (const auto &each : src)
    {

        // applying filter criterias
        bool filters = matchGenre(each, params.genre) &&
                       matchType(each, params.type) &&
                       matchRating(each, params.min_rating);
        // matchEpisodesCount(each, params.max_episodes);

        if (filters)
        {
            filteredList.push_back(&each);
            count++;
            if (filteredList.size() >= params.limit)
            {
                break;
            }
        }
    }
    std::string message = "Filtered Count: " + std::to_string(count);
    messageLogger.message(message.c_str(), Log::Loglevel::App);
    return filteredList;
}