#include "../include/FormatJSON.hpp"

std::string FormatJSON::FormatTrackJson(){
   nlohmann::json track_json = GetJsonObject();
   std::string name, artists, album, duration_ms, release_date, popularity, is_explicit;
   std::vector<std::string> external_urls;

   name = track_json["name"];
   artists = ;
   album;
   duration_ms;
   release_date;
   popularity;
   is_explicit;
}

std::string FormatJSON::FormatPlaylistJson(){
   std::string collaborative, owner, followers, total_tracks, description, name;
   std::vector<std::string> external_urls;

}

std::string FormatJSON::FormatArtistJson(){
   std::string followers, name, popularity;
   std::vector<std::string> genres_vec, external_urls; 

}  

std::string FormatJSON::FormatAlbumJson(){
   std::vector<std::string> tracks, external_urls; 
   std::string artist_name, album_name, release_date, album_type;
}

std::string FormatJSON::FormatUserProfileJson(){
   std::string display_name, external_url, followers, id;
}