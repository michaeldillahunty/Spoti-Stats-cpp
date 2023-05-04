#include "Artist.h"

Artist::Artist(nlohmann::json artist_json) : BasicSpotify(artist_json) {
   for (auto it = artist_json["external_urls"].begin(); it != artist_json["external_urls"].end(); ++it)
      external_urls[it.key()] = it.value();

   href = artist_json["href"];
   id = artist_json["id"];
   name = artist_json["name"];
   type = artist_json["type"];
   uri = artist_json["uri"];

   followers = artist_json["followers"];
   genres = artist_json["genres"];
   popularity = artist_json["popularity"];
}

int Artist::GetFollowers() const{ return followers; }

int Artist::GetPopularity() const { return popularity; }

std::string Artist::GetName() const { return name; }

std::vector<std::string> Artist::GetGenres() const { return genres; }
