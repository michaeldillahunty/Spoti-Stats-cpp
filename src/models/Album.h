#ifndef ALBUM_H
#define ALBUM_H

#include "BasicSpotify.h"
#include "Track.h"
#include "Artist.h"

class Album : public BasicSpotify {
   private:
      std::string album_type;
      int total_tracks;
      std::string name; 
      std::string release_date;
      std::string release_date_precise; 
      /* restrictions */
      /* copyrights */
      std::vector<std::string> genres; 
      std::string label;
      int popularity; 
      std::vector<std::shared_ptr<Track>> tracks;
      std::vector<std::shared_ptr<Artist>> artists;
   

   public:
      Album(nlohmann::json album_json);

      std::string GetAlbumType();
      int GetTotalTracks();
      std::string GetName();
      std::string GetReleaseDate();
      std::string GetReleaseDatePrecise();
      std::vector<std::string> GetGenres();
      std::string GetLabel();
      int GetPopularity();
      std::vector<std::shared_ptr<Artist>> GetArtists();
      std::vector<std::shared_ptr<Track>> GetTracks();

      std::map<std::string, std::string> GetExternalUrls() const override; 
      std::string GetHref() const override;
      std::string GetId() const override;
      std::string GetType() const override;
      std::string GetUri() const override;

      virtual ~Album(){};
};

#endif