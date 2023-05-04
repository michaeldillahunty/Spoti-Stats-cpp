#ifndef TRACK_H
#define TRACK_H

#include "Artist.h"

class Track {
   private:
      std::vector<std::shared_ptr<Artist>> artists;
      int duration_ms;
      bool is_explicit;
      std::map<std::string, std::string> external_urls;
      std::string href;
      std::string id;
      bool is_playable;
      std::string name;
      std::string preview_url;
      int track_number;
      std::string type;
      std::string uri;

   public:
      Track(nlohmann::json track_json);

      std::vector<std::shared_ptr<Artist>> GetArtist() const;
      int GetDurationMs() const; 
      bool IsExplicit() const;
      std::map<std::string, std::string> GetExternalUrls() const;
      std::string GetHref() const;
      std::string GetId() const;
      bool IsPlayable() const;
      std::string GetName() const;
      std::string GetPreviewUrl() const;
      int GetTrackNumber() const;
      std::string GetType() const;
      std::string GetUri() const;
      // std::shared_ptr<TrackLink> GetLinkedFrom() const;
};


#endif