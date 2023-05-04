#ifndef ARITST_H
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
};
#endif 