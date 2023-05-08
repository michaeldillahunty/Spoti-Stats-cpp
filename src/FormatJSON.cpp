#include "../include/FormatJSON.hpp"

std::string FormatJSON::FormatTrackJson(){
   nlohmann::json track_json = GetJsonObject();
   std::string name, album, duration_ms, release_date, popularity, is_explicit;
   std::vector<std::string> external_urls;
   std::vector<nlohmann::json> artists;

   name = track_json["name"];
   album = track_json["album"]["name"];
   duration_ms = track_json["duration_ms"];
   release_date = track_json["album"]["release_date"];
   is_explicit = track_json["explicit"] ? "true" : "false";

   for (nlohmann::json artist_json : track_json["artists"]){
      std::string artist_name = artist_json["name"];
      artists.push_back(artist_json);
      external_urls.push_back(artist_json["external_urls"]["spotify"]);
   }

   nlohmann::json result {
         {"name", name},
         {"artists", artists},
         {"album", album},
         {"duration_ms", duration_ms},
         {"release_date", release_date},
         {"popularity", track_json["popularity"]},
         {"is_explicit", is_explicit},
         {"external_urls", external_urls}
   };
}

std::string FormatJSON::FormatPlaylistJson(){
   nlohmann::json playlist_json = GetJsonObject();
   std::string collaborative, owner, followers, total_tracks, description, name;
   std::vector<std::string> external_urls;

   collaborative = playlist_json["collaborative"];
   owner = playlist_json["owner"]["display_name"];
   followers = playlist_json["followers"]["total"];
   total_tracks = playlist_json["tracks"]["total"];
   description = playlist_json["description"];
   name = playlist_json["name"];

   for (auto it = playlist_json["external_urls"].begin(); it != playlist_json["external_urls"].end(); ++it)
      external_urls.push_back(it.value());

   nlohmann::json formatted_json = {
      {"name", name},
      {"collaborative", collaborative},
      {"owner", owner},
      {"followers", followers},
      {"total_tracks", total_tracks},
      {"description", description},
      {"external_urls", external_urls}
   };

   return formatted_json.dump();
}

std::string FormatJSON::FormatArtistJson(){
   nlohmann::json artist_json = GetJsonObject();
   std::string followers, name, popularity;
   std::vector<std::string> genres_vec, external_urls; 

   name = artist_json["name"];
   popularity = artist_json["popularity"];
   followers = artist_json["followers"]["total"];

   // Extract genres from the JSON array and add them to the vector
   for (const auto& genre : artist_json["genres"]) {
      genres_vec.push_back(genre);
   }

   // Extract external URLs from the JSON array and add them to the vector
   for (const auto& url : artist_json["external_urls"].items()) {
      external_urls.push_back(url.value());
   }
}  

std::string FormatJSON::FormatAlbumJson(){
   std::vector<std::string> tracks, external_urls; 
   std::string artist_name, album_name, release_date, album_type;
}

std::string FormatJSON::FormatUserProfileJson(){
   std::string display_name, external_url, followers, id;
}