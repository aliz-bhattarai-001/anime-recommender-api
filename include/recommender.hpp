#pragma once
#include "anime.h"
#include "../include/filter.hpp"
namespace Recommender {

	float score(const Anime& a, const QueryParams& params);
	std::vector<ScoredAnime> rank(const std::vector<const Anime*>& filtered, const QueryParams& params);
}