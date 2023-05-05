#include "Album.h"

Album::Album(nlohmann::json album_json) : BasicSpotify(album_json) {
   for(nlohmann::json json : album_json["artists"])
      artists.push_back(std::shared_ptr<Artist>(new Artist(json)));
   
   for(nlohmann::json json : album_json["tracks"])
      tracks.push_back(std::shared_ptr<Track>(new Track(json)));
   
   album_type = album_json["album_type"];
   total_tracks = album_json["total_tracks"];
   name = album_json["name"];
   release_date = album_json["release_date"];
   release_date_precise = album_json["release_date_precision"];
   genres = album_json["genres"];
   label = album_json["label"];
   popularity = album_json["popularity"];
}

std::string Album::GetAlbumType() { return album_type; }

int Album::GetTotalTracks() { return total_tracks; }

std::string Album::GetName() { return name; }

std::string Album::GetReleaseDate() { return release_date; }

std::string Album::GetReleaseDatePrecise() { return release_date_precise; }

std::vector<std::string> Album::GetGenres() { return genres; }

std::string Album::GetLabel() { return label; }

int Album::GetPopularity() { return popularity; }

std::vector<std::shared_ptr<Artist>> Album::GetArtists() { return artists; }

std::vector<std::shared_ptr<Track>> Album::GetTracks() { return tracks;}

std::map<std::string, std::string> Album::GetExternalUrls() const {
   return BasicSpotify::GetExternalUrls();
}

std::string Album::GetHref() const {
   return BasicSpotify::GetHref();
}

std::string Album::GetId() const {
   return BasicSpotify::GetId();
}

std::string Album::GetType() const {
   return BasicSpotify::GetType();
}

std::string Album::GetUri() const {
   return BasicSpotify::GetUri();
}