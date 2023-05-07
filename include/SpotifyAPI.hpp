#ifndef SPOTIFY_API_HPP
#define SPOTIFY_API_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <vector> 
#include <cstdlib>
#include <cctype>
#include <algorithm>

#include "ClientNetwork.h"
#include "ServerNetwork.h"
#define MAX_MSG 512

/* Extra installed libraries and links:
   - libcurl (https://curl.se/libcurl/)
   - nlohmann/json (https://github.com/nlohmann/json)
*/ 
#include <curl/curl.h>
#include <nlohmann/json.hpp>

// #include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>


#define GUEST_OUTPUT_FILE "../GuestOutput.json"

// typedef template for storing and mapping CURL query options
// i.e. {"endpoint", "/v1/tracks/"}
typedef std::map<std::string, std::string>query_opt_t;

// using json = nlohmann::json;

class SpotifyAPI {
   private: 
      std::string client_id = "23ba501c09bd4194b3f2771c98fb5814";
      std::string client_secret = "eb80eac6f244443fae50300fc8db1479";

   public: 
      std::string encode_credentials(const std::string& client_id, const std::string& client_secret);
      // std::string get_auth_token(const std::string& client_id, const std::string& client_secret, const std::string& refresh_token);
      std::string request_authorization();
      std::string get_auth_token(const std::string& client_id, const std::string& client_secret);
      // void save_refresh_token(const std::string& refresh_token);
      // std::string get_refresh_token();
      std::string get_auth_header(const std::string& access_token);
      nlohmann::json api_request_test(const std::string& access_token, const std::string& user_id, const std::string& filename);

      /* Function that performs GET requests to SpotifyAPI */
      // nlohmann::json SpotifyCURL(std::string endpoint, std::map<std::string, std::string>options, std::string auth_token, std::string body); // function for custom HTTP GET Requests
      nlohmann::json SpotifyCURL(std::string endpoint, std::string auth_token); // function for standard HTTP GET Requests
      nlohmann::json SpotifyGET(std::string endpoint, std::map<std::string, std::string> options, std::string auth_token, std::string body = "");
      

      /* Functions for handling specific cURL GET requests: 
         - GetArtist 
         - GetAlbum
         - GetPlaylist (public playlist)
         - GetUser (public user profiles)
         - GetSong 
      */
      nlohmann::json GetPublicUser(std::string username, std::string auth_token);
      nlohmann::json GetSongID(std::string song_name, std::string auth_token);
      
      nlohmann::json SearchSongs(std::string song_name, query_opt_t options, std::string auth_token);
      nlohmann::json GetSong(std::string songID, std::string auth_token);
      nlohmann::json GetArtist(std::string artistID, std::string auth_token);


      std::string GetClientID() { return this->client_id; }
      std::string GetClientSecret() { return this->client_secret; }

};

using namespace web;
using namespace web::http;
using namespace web::http::client;
// Decorator Design Pattern (Move to new file once it works)
//
struct Decorator {
    virtual nlohmann::json perform_search(std::string search_value, const std::string auth_token) = 0;
};

class Search : public Decorator {
    http_client* search_client;
    uri_builder builder;

    public:
        nlohmann::json perform_search(std::string search_value, const std::string auth_token) override {
            // the base perform_search just initiates the member values
            // these are used for every search
            search_client = new http_client(U("https://api.spotify.com/v1/search"));
            
            builder.append_query(U("q"), utility::conversions::to_utf8string(search_value));
            builder.append_query(U("limit"), 5); // only return the top 5 tracks with the given name
            builder.append_query(U("market"), U("US"));  // Only search in US market
            
            std::cout << "QUERY: " << builder.query() << std::endl;

            return std::string("Spotify Search Initiated\n");
        }
    
    http_client* get_client() {
        return search_client;
    }
    
    uri_builder get_builder() {
        return builder;
    }
};

class SearchTrack : public Decorator {
    Search& search;

    public:
    SearchTrack(Search& s): search{s} {}

    nlohmann::json perform_search(std::string search_value, const std::string auth_token) override {
        // set the values for builder and client
        search.perform_search(search_value, auth_token);
        
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
           throw std::runtime_error("Failed to get song id");
        }
        
        int arr_size = json_obj["tracks"]["items"].size();
        std::string name;
        std::string artist;
        std::string id;
        for (int i=0; i<arr_size; i++) {
            name = json_obj["tracks"]["items"][i]["name"];
            id = json_obj["tracks"]["items"][i]["id"];
            artist = json_obj["tracks"]["items"][i]["artists"][0]["name"];
            
            std::cout << "Name, Artist, ID: " << name << ", " << artist << ", " << id << std::endl;
        }
        
        return json_obj;

    }
};


#endif
