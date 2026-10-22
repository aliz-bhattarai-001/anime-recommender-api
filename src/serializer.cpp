#include "../include/serializer.hpp"

std::string Serializer::typeToString(AnimeType t)
{
    switch (t)
    {
    case AnimeType::TV:
        return "TV";
    case AnimeType::Movie:
        return "Movie";
    case AnimeType::OVA:
        return "OVA";
    case AnimeType::Special:
        return "Special";
    default:
        return "Unknowned";
    }
}

std::string Serializer::errorJson(const std::string &message, int code)
{
    nlohmann::json errInfo;
    errInfo["error"] = message;
    errInfo["code"] = code;
    return errInfo.dump(2);
}

nlohmann::json Serializer::animeToJson(const ScoredAnime &a)
{
    nlohmann::json outJson;
    // seems like the arrangement on the json object is sorted alphabetically.

    outJson["title"] = a.ref->title;
    outJson["rating"] = a.ref->rating;
    outJson["episodes"] = a.ref->episodes;
    outJson["type"] = typeToString(a.ref->type);
    outJson["score"] = a.score;

    outJson["genres"] = nlohmann::json::array();
    for (const auto &genre : a.ref->genres)
    {
        outJson["genres"].push_back(genre);
    }
    return outJson;
}

std::string Serializer::toJson(const std::vector<ScoredAnime> &results)
{
    nlohmann::json arr = nlohmann::json::array();

    for (const auto &each : results)
    {
        arr.push_back(animeToJson(each));
    }
    return arr.dump(2);
}