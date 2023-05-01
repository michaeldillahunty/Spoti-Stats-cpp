#ifndef SPOTIFY_API_HPP
#define SPOTIFY_API_HPP

#include <iostream>
#include <sstream>
#include <string>

/* Extra installed libraries and links:
   - libcurl (https://curl.se/libcurl/)
   - nlohmann/json (https://github.com/nlohmann/json)
   - cpr (https://github.com/whoshuu/cpr)
*/ 
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;

class SpotifyAPI {
   private: 
      // std::string _client_id;
      // std::string _client_secret;

      // std::string username; 
      // std::string password; 

   public: 
      // void set_credentials(std::string, std::string);
      // std::string get_credentials(); 
      std::string encode_credentials(const std::string& client_id, const std::string& client_secret);
      std::string get_auth_token(const std::string& client_id, const std::string& client_secret);
      std::string get_auth_header(const std::string& access_token);
      json api_request_test(const std::string& access_token, const std::string& user_id, const std::string& filename);


};

#endif