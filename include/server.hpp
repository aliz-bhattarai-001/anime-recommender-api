#pragma once

#include <iostream>
#include "../include/anime.h"
#include "../include/dataloader.hpp"
#include "../include/filter.hpp"
#include "../include/recommender.hpp"
#include "../include/serializer.hpp"
#include "../include/queryparser.hpp"

#include "../vendor/httplib.h"


class Server {
public:
    
    explicit Server(const std::vector<Anime>& data);

    void listen(const std::string& host, int port);

private:
    
    void registerRoutes();

    
    void handleHealth(const httplib::Request& req, httplib::Response& res);
    void handleRecommend(const httplib::Request& req, httplib::Response& res);

   // shared by all functions...
    const std::vector<Anime>& data_; 
    httplib::Server svr_; 
};