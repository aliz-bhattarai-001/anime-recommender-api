#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <optional>
#include "./anime.h"


namespace DataLoader {

std::vector<int> mapHeaders(const std::string& header_line);
std::vector<std::string> parseGenres(const std::string& raw);
AnimeType parseType(const std::string& raw);
std::optional<Anime> parseRow(const std::string& line, const std::vector<int>& col_map);
std::vector<Anime> load(const std::string& path);


};

namespace Helpers {

std::string trim(std::string s);
std::string toLower(std::string s);
std::vector<std::string> splitFields(const std::string& line);

};