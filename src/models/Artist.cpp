#include "Artist.h"

Artist::Artist(nlohmann::json artist_json) : BasicSpotify(artist_json) {
   for (auto it = artist_json["external_urls"].begin(); it != artist_json["external_urls"].end(); ++it)
      external_urls[it.key()] = it.value();
      
   followers = artist_json["followers"];
   genres = artist_json["genres"];
   artist_name = artist_json["name"];
   popularity = artist_json["popularity"];
}