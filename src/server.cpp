#include "../include/server.hpp"

// constructor 
Server::Server(const std::vector<Anime>& data)
    : data_(data)
{
    registerRoutes();
}

void Server::handleHealth(const httplib::Request& req, httplib::Response& res) {
    res.status = 200;
    std::string response = "{\"status\":\"ok\"}";
    res.set_content(response, "application/json");
}

void Server::listen(const std::string& host, int port) {
    std::cout << "Listening on http://" << host << ":" << port << std::endl;
    svr_.listen(host, port);
}

void Server::handleRecommend(const httplib::Request& req, httplib::Response& res) {
   std::string rawQuery;
    size_t position = req.target.find('?');

    if (position != std::string::npos) {
        rawQuery = req.target.substr(position + 1);
    }
    // if position == npos then rawQuery = "" so parse handles that empty string.

    QueryParams query = QueryParser::parse(rawQuery);

    std::optional<std::string> error = QueryParser::validate(query);
    if (error.has_value())
    {
        res.status = 400;
        res.set_content(Serializer::errorJson(*error, 400), "application/json");
        return;
    }

    std::vector<const Anime*> filteredList = Filter::apply(data_, query);
    if (filteredList.empty()) {
        res.status = 400;
        res.set_content(Serializer::errorJson("no results found.", 404), "application/json");
        return;
    }

    std::vector<ScoredAnime> results = Recommender::rank(filteredList, query);

    res.status = 200;
    res.set_content(Serializer::toJson(results), "application/json");
}


void Server::registerRoutes() {
    svr_.Get("/recommend",
        [this](const httplib::Request& req, httplib::Response& res) {
            handleRecommend(req, res);
        });


    svr_.Get("/health",
        [this](const httplib::Request& req, httplib::Response& res) {
            handleHealth(req, res);
        });

}