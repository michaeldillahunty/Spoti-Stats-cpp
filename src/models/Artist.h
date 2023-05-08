#ifndef ARTIST_H
#define ARTIST_H

#include "BasicSpotify.h"
#include <nlohmann/json.hpp>

class Artist : public BasicSpotify {

   private:
      int followers; 
      std::vector<std::string> genres; 
      std::string artist_name; 
      int popularity; 

   public:
      Artist(nlohmann::json artist_json);

      std::string FormatSpotifyJson() override;
      std::string GetId() const override; 
      std::string GetExternalUrls() const override;
      std::string GetName() const override; 
      std::string GetType() const override; 

      virtual ~Artist(){};      
};
#endif 