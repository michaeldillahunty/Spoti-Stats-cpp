#include "Track.h"

Track::Track(nlohmann::json track_json) : BasicSpotify(track_json) {
      // std::vector<std::shared_ptr<Artist>> artists; 
      // std::string preview_url;
      // std::string track_name; 
      // int track_number;
      // int duration_ms; 
      // int is_explicit;
      // std::vector<std::shared_ptr<Track>> tracks; 

      for (const auto& json : track_json["artists"]){
         Artist*artist = new Artist(json);
         artists.push_back(artist);
      }
}