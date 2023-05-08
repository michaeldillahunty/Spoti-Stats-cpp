#include "../include/DetailedSearch.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::client;

/*
 
 Each of these functions will return a json object with information about the spotify object with the given id
 
 */
nlohmann::json DetailedSearch::detailed_search(std::string endpoint, std::string id, std::string auth_token) {
    
    std::string url = "https://api.spotify.com/" + endpoint + id;
    http_client search_client(U(url));
    
    http_request req(methods::GET);
    req.headers().add(U("Authorization"), utility::conversions::to_utf8string("Bearer " + auth_token));
    http_response response = search_client.request(req).get();
    
    // check for valid status code and parse response to json object if OK
    nlohmann::json json_obj;
    if (response.status_code() == status_codes::OK) {
       json_obj = nlohmann::json::parse(response.extract_utf8string().get());
       json_obj.erase("available_markets");
    } else {
       throw std::runtime_error("Failed to get spotify details");
    }
    return json_obj;
}

