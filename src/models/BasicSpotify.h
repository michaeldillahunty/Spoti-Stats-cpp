#ifndef BASIC_SPOTIFY_H
#define BASIC_SPOTIFY_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <vector> 
#include <cstdlib>
#include <cctype>
#include <algorithm>

#include <nlohmann/json.hpp>


class BasicSpotify {
   protected:
      std::string name; 
      std::string id;
      std::map <std::string, std::string> external_urls;
      std::string type; 
      
   public:
      BasicSpotify(nlohmann::json json_obj);
      virtual std::string FormatSpotifyJson() = 0;
      virtual std::string GetId() const { return id; }
      virtual std::string GetExternalUrls() const { return external_urls.at("spotify"); }
      virtual std::string GetName() const { return name; }      
      virtual std::string GetType() const { return type; }


      virtual ~BasicSpotify(){};
};


#endif  