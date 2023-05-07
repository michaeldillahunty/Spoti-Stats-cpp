#ifndef SPOTIFY_CREATOR_HPP
#define SPOTIFY_CREATOR_HPP

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

/*
   This is the abstract/creator class
*/

class SpotifyCreator {
   public:
      // base class creation method
      virtual nlohmann::json Search(std::string endpoint, std::map<std::string, std::string> options, std::string auth_token, std::string body="") = 0;
      virtual ~SpotifyCreator(){};
};

#endif 