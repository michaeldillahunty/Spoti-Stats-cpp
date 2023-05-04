#include "Track.h"

Track::Track(nlohmann::json track_json){
   for(nlohmann::json json : track_json["artists"])
      artists.push_back(std::shared_ptr<Artist>(new Artist(json)));
   
   duration_ms = track_json["duration_ms"];
   is_explicit = track_json["explicit"];

   for (auto it = track_json["external_urls"].begin(); it != track_json["external_urls"].end(); ++it)
      external_urls[it.key()] = it.value();

   href = track_json["href"];
   id = track_json["id"];
   name = track_json["name"];

   if(!track_json["preview_url"].is_null())
      preview_url = track_json["preview_url"];

   track_number = track_json["track_number"];
   type = track_json["type"];
   uri = track_json["uri"];
}

std::vector<std::shared_ptr<Artist>> Track::GetArtist() const { return artists; }

int Track::GetDurationMs() const { return duration_ms; } 

bool Track::IsExplicit() const { return is_explicit; }

std::map<std::string, std::string> Track::GetExternalUrls() const { return external_urls; }

std::string Track::GetHref() const { return href; }

std::string Track::GetId() const { return id; }

bool Track::IsPlayable() const { return is_playable; }

std::string Track::GetName() const { return name; }

std::string Track::GetPreviewUrl() const { return preview_url; }

int Track::GetTrackNumber() const { return track_number; }

std::string Track::GetType() const { return type; }

std::string Track::GetUri() const { return uri; }