#include "Track.h"



Track::Track(nlohmann::json track_json) : BasicSpotify(track_json) {
   for(nlohmann::json json : track_json["artists"])
      artists.push_back(std::shared_ptr<Artist>(new Artist(json)));
   
   duration_ms = track_json["duration_ms"];
   is_explicit = track_json["explicit"];

   name = track_json["name"];

   if(!track_json["preview_url"].is_null())
      preview_url = track_json["preview_url"];

   track_number = track_json["track_number"];
}

// class specific methods
std::vector<std::shared_ptr<Artist>> Track::GetArtist() const { return artists; }

std::string Track::GetName() const { return name; }

int Track::GetTrackNumber() const { return track_number; }

int Track::GetDurationMs() const { return duration_ms; } 

bool Track::IsExplicit() const { return is_explicit; }

bool Track::IsPlayable() const { return is_playable; }

std::string Track::GetPreviewUrl() const { return preview_url; }

std::map<std::string, std::string> Track::GetExternalUrls() const {
   return BasicSpotify::GetExternalUrls();
}

std::string Track::GetHref() const {
   return BasicSpotify::GetHref();
}

std::string Track::GetId() const {
   return BasicSpotify::GetId();
}

std::string Track::GetType() const {
   return BasicSpotify::GetType();
}

std::string Track::GetUri() const {
   return BasicSpotify::GetUri();
}