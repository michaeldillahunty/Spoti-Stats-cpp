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
      BasicSpotify(nlohmann::json json_obj){
         for (auto it = json_obj["external_urls"].begin(); it != json_obj["external_urls"].end(); ++it)
            external_urls[it.key()] = it.value();

         href = json_obj["href"];
         id = json_obj["id"];
         type = json_obj["type"];
         uri = json_obj["uri"];
      }

      virtual std::map<std::string, std::string> GetExternalUrls() const {
         return external_urls;
      }
      virtual std::string GetHref() const {
         return href; 
      }
      virtual std::string GetId() const {
         return id; 
      }
      virtual std::string GetType() const {
         return type;
      }
      virtual std::string GetUri() const {
         return uri; 
      }
      virtual ~BasicSpotify(){};
};


#endif  