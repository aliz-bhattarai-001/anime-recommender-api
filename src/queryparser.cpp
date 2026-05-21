#include "../include/queryparser.hpp"
#include <sstream>

std::string QueryParser::urlDecode(const std::string& src) {
    std::string result;
    for (int i = 0; i < src.size(); i++) {
        if (src[i] == '+')
            result += " ";
        else if (src[i] == '%' && (i + 2) < src.size()) {
        // (i + 2) < src.size() : prevents out of bound access.
            try {

                std::string hexVal = src.substr(i + 1, 2); // substr(starting index , count);
                int intVal = std::stoi(hexVal, nullptr, 16); // base : 16
                result += static_cast<char>(intVal);
                i += 2;
            } catch (std::exception& ){
                // if conversion fails : % is treated as literal '%' and continue.
                result += src[i];
            }
        } else {
            result += src[i];
        }
    }
    return result;
}

std::optional<std::string> QueryParser::validate(const QueryParams& params) {
    if (params.min_rating < 0.0f || params.min_rating > 10.0f)
        return "Min rating must be between : 0.0 and " + std::to_string(MAX_RATING);

    if (params.limit < 1 || params.limit > MAX_LIMIT) 
        return "limit must be between 1 and " + std::to_string(MAX_LIMIT);
    

    if (params.max_episodes < 0)
        return "Max episodes can't be negative.";
    return "";
}

QueryParams QueryParser::parse(const std::string& raw_query) {
    QueryParams query = {
        .genre = "All",
        .type = "TV",
       .min_rating = 0.0f,
        .max_episodes = DEFAULT_MAX_EPISODES,
        .limit = DEFAULT_LIMIT
    };

    if (raw_query.empty())
        return query;

    std::stringstream ss(raw_query);
    std::string token;

    while (std::getline(ss, token, '&')) {
        if (token.empty())
            continue;

        size_t symbol = token.find('=');
        if (symbol == std::string::npos)
            continue;

       std::string key = urlDecode(token.substr(0, symbol));
       std::string value = urlDecode(token.substr(symbol + 1));

       if (key.empty())
           continue;

       // assigning values to the QueryParam variable.
       if (key == "genre" || key == "genres")
           query.genre = value;
       else if (key == "type")
           query.type = value;
       else if (key == "min_rating") {
           try {
               query.min_rating = std::stof(value);
           } catch (std::exception&) {
               query.min_rating = 0.0f;
           }
       } else if (key == "limit") {
           try {
               query.limit = std::stoi(value);
           } catch (std::exception&) {
               query.limit = 0;
           }
       } else if (key == "max_episodes") {
           try {
               query.max_episodes = std::stoi(value);
           } catch (std::exception&) {
               query.max_episodes = 0;
           }
       }
    }

    // if negative or 0 is set as limit resort to default limit.
    if (query.limit <= 0)
        query.limit = DEFAULT_LIMIT;
    

    return query;

}

