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
      std::map<std::string, std::string> external_urls; 
      std::string href; 
      std::string id;
      std::string type;
      std::string uri;

   public:
      BasicSpotify(nlohmann::json json_obj);

      std::map<std::string, std::string> GetExternalUrls() const {
         return external_urls;
      }
      std::string GetHref() const {
         return href; 
      }
      std::string GetId() const {
         return id; 
      }
      std::string GetType() const {
         return type;
      }
      std::string GetUri() const {
         return uri; 
      }

};


#endif 