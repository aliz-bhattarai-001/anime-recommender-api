#pragma once

#include "anime.h"
#include <optional>

namespace QueryParser
{
    std::string urlDecode(const std::string &src);
    std::optional<std::string> validate(const QueryParams &params);
    QueryParams parse(const std::string &raw_query);

};