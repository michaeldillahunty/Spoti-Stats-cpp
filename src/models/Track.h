#ifndef TRACK_H
#define TRACK_H

#include "BasicSpotify.h"
#include "Artist.h"
#include <nlohmann/json.hpp>

class Track : public BasicSpotify {
   private:
      std::vector<Artist*> artists; 
      std::string preview_url;
      std::string track_name; 
      int track_number;
      int duration_ms; 
      int is_explicit;
      std::vector<std::shared_ptr<Track>> tracks; 

   public:
      Track(nlohmann::json json_obj);
      std::string FormatSpotifyJson() override; 

      virtual ~Track(){
         for (Artist* artist : artists) {
            delete artist;
         }
      };
};


#endif