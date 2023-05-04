#ifndef ARITST_H
#define ARTIST_H

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
// #include "../../include/SpotifyAPI.hpp"


class Artist {
   private:
      std::map<std::string, std::string> external_urls;
      std::string href;
      std::string id;
      std::string name;
      std::string type;
      std::string uri;

   public:
      Artist(nlohmann::json artist_json);

      std::map<std::string, std::string>GetExternalURLs() const;
      std::string GetHref() const;
      std::string GetID() const;
      std::string GetName() const;
      std::string GetType() const;
      std::string GetUri() const;       


};



#endif 