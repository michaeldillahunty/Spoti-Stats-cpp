#include "../include/Search.hpp"

/* Decorator Design Pattern:

   Search::perform_search sets up the client and uri builder to use later, top 5 will be returned in json form.
   SearchTrack::perform_search finishes uri_builder and send a search for Tracks
   SearchArtist::perform_search finishes uri_builder and send a search for Artists
   SearchAlbum::perform_search finishes uri_builder and send a search for Album
   SearchPlaylist::perform_search finishes uri_builder and send a search for Playlists
 
*/
nlohmann::json Search::perform_search(std::string search_value, const std::string auth_token) {
    // the base perform_search just initiates the member values
    // these are used for every search
    search_client = new http_client(U("https://api.spotify.com/v1/search"));
    
    builder.append_query(U("q"), utility::conversions::to_utf8string(search_value));
    builder.append_query(U("limit"), 5); // only return the top 5 tracks with the given name
    builder.append_query(U("market"), U("US"));  // Only search in US market

    return std::string("Spotify Search Initiated...");
}

nlohmann::json SearchTrack::perform_search(std::string search_value, const std::string auth_token) {
    // set the values for builder and client
    std::cout << search.perform_search(search_value, auth_token) << std::endl;
    
    uri_builder builder = search.get_builder();
    http_client* search_client = search.get_client();
    
    builder.append_query(U("type"), U("track"));

    // now all members are ready to perform a search
    http_request req(methods::GET);
    req.set_request_uri(builder.to_uri());
    req.headers().add(U("Authorization"), utility::conversions::to_utf8string("Bearer " + auth_token));

    // Send HTTP request and parse JSON response
    http_response response = search_client->request(req).get();
    nlohmann::json json_obj;
    std::cout << "Status Code: " << response.status_code() << std::endl;
    if (response.status_code() == status_codes::OK) {
       json_obj = nlohmann::json::parse(response.extract_utf8string().get());
       json_obj.erase("available_markets");
    } else {
       throw std::runtime_error("Failed to get track id");
    }
    
    return json_obj;
}

nlohmann::json SearchArtist::perform_search(std::string search_value, const std::string auth_token) {
    // set the values for builder and client
    std::cout << search.perform_search(search_value, auth_token) << std::endl;
    
    uri_builder builder = search.get_builder();
    http_client* search_client = search.get_client();
    
    builder.append_query(U("type"), U("artist"));

    // now all members are ready to perform a search
    http_request req(methods::GET);
    req.set_request_uri(builder.to_uri());
    req.headers().add(U("Authorization"), utility::conversions::to_utf8string("Bearer " + auth_token));

    // Send HTTP request and parse JSON response
    http_response response = search_client->request(req).get();
    nlohmann::json json_obj;
    std::cout << "Status Code: " << response.status_code() << std::endl;
    if (response.status_code() == status_codes::OK) {
       json_obj = nlohmann::json::parse(response.extract_utf8string().get());
       json_obj.erase("available_markets");
    } else {
       throw std::runtime_error("Failed to get artist id");
    }
    
    return json_obj;
}

nlohmann::json SearchAlbum::perform_search(std::string search_value, const std::string auth_token) {
    // set the values for builder and client
    std::cout << search.perform_search(search_value, auth_token) << std::endl;
    
    uri_builder builder = search.get_builder();
    http_client* search_client = search.get_client();
    
    builder.append_query(U("type"), U("album"));

    // now all members are ready to perform a search
    http_request req(methods::GET);
    req.set_request_uri(builder.to_uri());
    req.headers().add(U("Authorization"), utility::conversions::to_utf8string("Bearer " + auth_token));

    // Send HTTP request and parse JSON response
    http_response response = search_client->request(req).get();
    nlohmann::json json_obj;
    std::cout << "Status Code: " << response.status_code() << std::endl;
    if (response.status_code() == status_codes::OK) {
       json_obj = nlohmann::json::parse(response.extract_utf8string().get());
       json_obj.erase("available_markets");
    } else {
       throw std::runtime_error("Failed to get album id");
    }
    
    return json_obj;
}

nlohmann::json SearchPlaylist::perform_search(std::string search_value, const std::string auth_token) {
    // set the values for builder and client
    std::cout << search.perform_search(search_value, auth_token) << std::endl;
    
    uri_builder builder = search.get_builder();
    http_client* search_client = search.get_client();
    
    builder.append_query(U("type"), U("playlist"));
    builder.append_query(U("limit"), 10); 

    // now all members are ready to perform a search
    http_request req(methods::GET);
    req.set_request_uri(builder.to_uri());
    req.headers().add(U("Authorization"), utility::conversions::to_utf8string("Bearer " + auth_token));

    // Send HTTP request and parse JSON response
    http_response response = search_client->request(req).get();
    nlohmann::json json_obj;
    std::cout << "Status Code: " << response.status_code() << std::endl;
    if (response.status_code() == status_codes::OK) {
       json_obj = nlohmann::json::parse(response.extract_utf8string().get());
       json_obj.erase("available_markets");
    } else {
       throw std::runtime_error("Failed to get playlist id");
    }
    
    return json_obj;
}

// the Spotify API endpoint for getting a public user's profile has a different endpoint than the previous searches
nlohmann::json SearchPublicUser::perform_search(std::string search_value, const std::string auth_token) {


/*       std::string encoded_uid = "";
   for (const auto& c : search_value) {
      if (c == ' ') {
         encoded_uid += "%20";
      } else {
         encoded_uid += c;
      }
   }
   
   // set the values for builder and client
   http_client* search_client = new http_client(U("https://api.spotify.com/v1/"));
   uri_builder builder(U("/users/" + encoded_uid));
   http_request req(methods::GET);
   req.set_request_uri(builder.to_uri());
   req.headers().add(U("Authorization"), utility::conversions::to_utf8string("Bearer " + auth_token));

   // Send HTTP request and parse JSON response
   http_response response = search_client->request(req).get();
   nlohmann::json json_obj;
   std::cout << "Status Code: " << response.status_code() << std::endl;
   if (response.status_code() == status_codes::OK) {
      json_obj = nlohmann::json::parse(response.extract_utf8string().get());
   } else {
      throw std::runtime_error("Failed to get user: " + search_value);
   }
   
   return json_obj; */
}