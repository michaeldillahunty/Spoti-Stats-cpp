#ifndef ALBUM_H
#define ALBUM_H

#include "BasicSpotify.h"

class Album : public BasicSpotify {
   private:
      std::string album_type;
      int total_tracks;
      std::string name; 
      std::string release_date;
      std::string release_date_precise; 
      /* restrictions */
      /* copyrights */
      std::vector<std::strings> genres; 
      

      


   public:
      Album(nlohmann::json album_json);
};

#endif