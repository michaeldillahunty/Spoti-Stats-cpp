#ifndef GUEST_HPP
#define GUEST_HPP

#include "SpotifyAPI.hpp"

class Guest : public SpotifyAPI {

   public: 
      /* Inherited Methods */
      std::string encode_credentials(const std::string& client_id, const std::string& client_secret);
      std::string get_auth_token(const std::string& client_id, const std::string& client_secret);
      std::string get_auth_header(const std::string& access_token);
      json SpotifyGET(std::string endpoint, std::map<std::string, std::string> options, std::string auth_token, std::string body = "");

      /* New Methods */

};


#endif