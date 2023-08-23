#include "../include/DetailedSearch.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::client;

/**
 * @param endpoint the Spotify api endpoint
 * @param id the `id` for the endpoint trying to be called
 * @param auth_token passing the OAuth token 
 * @return json object containing the data about the selected song
 */
nlohmann::json DetailedSearch::detailed_search(std::string endpoint, std::string id, std::string auth_token) {
    std::string url = "https://api.spotify.com/" + endpoint + id;
    http_client search_client(U(url));
    
    http_request req(methods::GET);
    req.headers().add(U("Authorization"), utility::conversions::to_utf8string("Bearer " + auth_token));
    http_response response = search_client.request(req).get();
    
    // Check for valid status code and parse response to json object if OK
    nlohmann::json json_obj;
    
    if (response.status_code() == status_codes::OK) {
        json_obj = nlohmann::json::parse(response.extract_utf8string().get());
        // std::cout << "JSON OBJ BEFORE: " << json_obj << std::endl;
        // if the album property has a "available_markets" property -> delete it
        if (json_obj["album"].contains("available_markets")) {
            json_obj["album"].erase("available_markets");
        }
        json_obj.erase(("available_markets"));
        
        // std::cout << "JSON OBJ AFTER: " << json_obj << std::endl;
    } else {
        throw std::runtime_error("Failed to get spotify details");
    }
    return json_obj;
}

