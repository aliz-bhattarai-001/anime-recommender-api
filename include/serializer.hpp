#pragma once
#include "../include/anime.h"
#include "../vendor/json.hpp"
namespace Serializer {
std::string typeToString(AnimeType t);
std::string errorJson(const std::string& message, int code);
nlohmann::json animeToJson(const ScoredAnime& a);
std::string toJson(const std::vector<ScoredAnime>& results);

};
