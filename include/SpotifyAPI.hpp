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
    nlohmann::json perform_search(std::string search_value, const std::string auth_token) override;
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

    nlohmann::json perform_search(std::string search_value, const std::string auth_token) override;
};


#endif
