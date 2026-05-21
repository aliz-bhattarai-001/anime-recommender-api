#include "../include/dataloader.hpp"
#include "../include/logging.hpp"
#include <algorithm> // Required for std::transform
#include <cctype> // Req for std::tolower
#include <sstream> // Req for std::stringstream

#define MAX_LIMIT 10000

Log logger;

// basically removes the whitespace characters.
std::string Helpers::trim(std::string s)
{
    const std::string WHITESPACE = " \n\r\t\f\v";

    size_t start = s.find_first_not_of(WHITESPACE);

    if (start == std::string::npos)
        return ""; 
    // npos (-1) : no position found.
    // if the entire string is composed of whitespace chars.
    // return an empty string.

    size_t end = s.find_last_not_of(WHITESPACE);
    int new_length = end - start + 1; // the total characters
    return s.substr(start, new_length); //2nd arg = count of chars
}


// since & reference is not passed 
// it does not modify the original string but returns a copy
std::string Helpers::toLower(std::string s) {

    // a lamda function to pass in as rule to transform func
    // tells the transform func on how exactly to transform the data.
    auto toLowerChar = [](unsigned char c) { 
        return static_cast<unsigned char>(std::tolower(c)); 
        };

    // args: start, end, where to write (postion) 
    // -> s.begin() in 3rd arg:  just means write in that same string
    std::transform(s.begin(), s.end(), s.begin(),toLowerChar);
    return s;
}


std::vector<std::string> Helpers::splitFields(const std::string& line)
{
    std::vector<std::string> data;
    std::string currentValue ; 
    // initializes by default constructor to an empty string 
    bool isInsideQuotes = false;

    for (char ch : line) {
        if (ch == '"') // works as toggle for " " as well as skips their addition.
            isInsideQuotes = !isInsideQuotes;
        else if (ch == ',' && !isInsideQuotes) {
           data.push_back(trim(currentValue));
            currentValue.clear(); // clears the currentValue Buffer
        } else {
            currentValue += ch;
        }
    }

    // last value wouldn't have trailing commas afterwards.
    // so to push it back.
    data.push_back(trim(currentValue));
    return data;

}


/*
INDEX -> FIELD 

0 -> "name" (title)
1 -> "genre" 
2 -> "type"
3 -> "episodes"
4 -> "rating"

*/
std::vector<int> DataLoader::mapHeaders(const std::string& header_line)
{
    std::vector<std::string> fields = Helpers::splitFields(header_line);

    // initializing a vector of size 5 with each initialized to -1.
    // initializing to -1 makes it easier to check if the vector is -1 (not filled yet).
    std::vector<int> column_map(5, -1);
    for (int i = 0; i < fields.size(); i++) {
        std::string name = Helpers::toLower(Helpers::trim(fields[i]));

        if (name == "name")
            column_map[0] = i;
        else if (name == "genre")
            column_map[1] = i;
        else if (name == "type")
            column_map[2] = i;
        else if (name == "episodes")
            column_map[3] = i;
        else if (name == "rating")
            column_map[4] = i;
    }


    const char* fieldNames[] = { "name", "genres", "type", "episodes", "rating" };
    for (int i = 0; i < 5; i++) {
        if (column_map[i] == -1) { // if not replaced from its initialized (-1) : not found
            throw std::runtime_error(
                std::string("Missing Required column: ") + fieldNames[i]);
        }
    }
    return column_map;
}


std::vector<std::string> DataLoader::parseGenres(const std::string& raw)
{
    std::vector<std::string> data;
    std::stringstream ss(raw);
    std::string value;

    while (std::getline(ss, value, ',')) {
        std::string genre = Helpers::toLower(Helpers::trim(value));
        if (!genre.empty())
            data.push_back(genre);
    }

    return data;
}



AnimeType DataLoader::parseType(const std::string& raw) {
    std::string type = Helpers::toLower(Helpers::trim(raw));

    if (type == "tv")
        return AnimeType::TV;
    else if (type == "ova")
        return AnimeType::OVA;
    else if (type == "movie")
        return AnimeType::Movie;
    else if (type == "special")
        return AnimeType::Special;
    else
        return AnimeType::Unknowned;

}



std::optional<Anime> DataLoader::parseRow(const std::string& line, const std::vector<int>& column_map)
{
    std::vector<std::string> fields = Helpers::splitFields(line);
    
    int maxIndex = *std::max_element(column_map.begin(), column_map.end());
    if ((int)fields.size() <= maxIndex) {
        return std::nullopt;
    }

    Anime anime;
    // column_map[0] stores the index at which the anime title was found in the fields.
    // thus fields[column_map[0]] just means fields[titleIndex]

    anime.title = Helpers::trim(fields[column_map[0]]);
    if (anime.title.empty())
        return std::nullopt;

    anime.genres = parseGenres(fields[column_map[1]]);
    if (anime.genres.empty())
        return std::nullopt;

    anime.type = parseType(fields[column_map[2]]);
    //no need for empty checking : "Unknowned" type -> in case of absence

     try {
        anime.episodes = std::stoi(fields[column_map[3]]);
    } catch (const std::exception&) {
        anime.episodes = 0;
    }

    // rating — blank or non-numeric -> Skip that row.
    try {
        anime.rating = std::stof(fields[column_map[4]]);
    } catch (const std::exception&) {
        return std::nullopt;
    }

    return anime;
}



std::vector<Anime> DataLoader::load(const std::string& path) {
    // opening file for reading.
    std::ifstream thefile(path.c_str());

    if (!thefile.is_open()) {
        logger.message("Could Not Open File.", Log::Loglevel::Error);
        throw std::runtime_error("Critical Error: Could not open " + path);
    }

    std::vector<Anime> datalist;
    std::string line;

    if (!std::getline(thefile, line)) {
        throw std::runtime_error("File is empty: " + path);
    }
    
    // header row : mapping
    std::vector<int> col_map = mapHeaders(line);
    
    int skipped = 0;
    int count = 0;

    while (std::getline(thefile, line) && count != MAX_LIMIT) {
        if (line.empty())
            continue;
        std::optional<Anime> result = parseRow(line, col_map);
        if (result.has_value())
            datalist.push_back(std::move(*result));
        // move plunders the content of result directly into the vector.
        // no expensive copy made : the ownership of data is transferred to the vector.
        else
            skipped++;
        count++;
    }
    std::string message = std::string("Loaded ") + std::to_string(datalist.size()) + " records.\nSkipped : " + std::to_string(skipped); //+ "\ncount : "+ std::to_string(count);
    logger.message(message.c_str(), Log::Loglevel::App);
    return datalist;
}





