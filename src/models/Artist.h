#ifndef ARTIST_H
#define ARTIST_H

#include "BasicSpotify.h"

class Artist : public BasicSpotify {

   private:
      int followers; 
      std::vector<std::string>genres; 
      std::string name; 
      int popularity; 
   
   public:
      Artist(nlohmann::json artist_json);

      int GetFollowers() const;
      int GetPopularity() const;
      std::string GetName() const;
      std::vector<std::string> GetGenres() const;

      std::map<std::string, std::string> GetExternalUrls() const override; 
      std::string GetHref() const override;
      std::string GetId() const override;
      std::string GetType() const override;
      std::string GetUri() const override;
      
      virtual ~Artist(){};
};
#endif 