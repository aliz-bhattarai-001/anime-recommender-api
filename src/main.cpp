#include <iostream>
#include "../include/anime.h"
#include "../include/dataloader.hpp"
#include "../include/filter.hpp"
#include "../include/recommender.hpp"
#include "../include/serializer.hpp"
#include "../include/queryparser.hpp"
#include "../include/server.hpp"
void test();
void test2();
int entryPoint();

int main()
{
//     test();
//     test2();
    entryPoint();
    std::cin.get();
    return 0;
}

void test() {
    std::cout << "Server Loaded" << std::endl;
    std::vector<Anime> Animelist = DataLoader::load("./data/anime.csv");

    QueryParams query;
    query.genre = "Adventure";
    query.limit = 10;
    query.min_rating = 8.0f;
    query.max_episodes = 2000;
    std::vector<const Anime*> filteredList = Filter::apply(Animelist, query);
    std::vector<ScoredAnime> scoredList = Recommender::rank(filteredList, query);
    for (const auto& each : scoredList) {
        std::cout << "Name: " << each.ref->title << std::endl;
        std::cout << "Score: " << each.score << std::endl;
        std::cout << "---" << std::endl;
    }

    std::string json = Serializer::toJson(scoredList);
    std::cout << json << "\n";

    std::cout << Serializer::errorJson("test error", 400) << "\n";
}

void test2(void) {
    QueryParams params = QueryParser::parse("genre=action&min_rating=7.5&limit=5&max_episodes=24");
    std::cout << "Genre: " << params.genre << std::endl;
    std::cout << "Min rating: " << params.min_rating << std::endl;
    std::cout << "Max episodes: " << params.max_episodes << std::endl;
    std::cout << "Limit: " << params.limit << std::endl;
    std::cout << "Type: " << params.type << std::endl;
}


int entryPoint() {
    std::vector<Anime> animeList;
    try {
        animeList = DataLoader::load("./data/anime.csv");
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << "Loaded " << animeList.size() << " Records." << std::endl;

    Server server(animeList);

    server.listen("localhost", 8080);
    return 0;
}