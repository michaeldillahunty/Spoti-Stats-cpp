#ifndef TRACK_H
#define TRACK_H

#include "BasicSpotify.h"
#include "Artist.h"


class Track : public BasicSpotify {
   private:
      std::vector<std::shared_ptr<Artist>> artists;
      std::string preview_url;
      std::string name; 
      int track_number;
      int duration_ms;
      bool is_explicit;
      bool is_playable;
      std::vector<std::shared_ptr<Track>> tracks; 

   public:
      Track(nlohmann::json track_json);

      std::vector<std::shared_ptr<Artist>> GetArtist() const;
      std::string GetName() const; 
      std::string GetPreviewUrl() const;
      int GetDurationMs() const; 
      int GetTrackNumber() const;
      bool IsExplicit() const;
      bool IsPlayable() const;

      std::map<std::string, std::string> GetExternalUrls() const override; 
      std::string GetHref() const override;
      std::string GetId() const override;
      std::string GetType() const override;
      std::string GetUri() const override; 

      virtual ~Track(){};
      
      
      // std::shared_ptr<TrackLink> GetLinkedFrom() const;
};


#endif