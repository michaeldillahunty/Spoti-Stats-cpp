#include "../include/SpotifyFactory.hpp"

template<typename T>
std::shared_ptr<T> SpotifyFactory::CreateSpotifyObject(nlohmann::json json_obj){
   std::string type = json_obj["type"];
   std::shared_ptr<T> obj_ptr; 
   if (type == "artist") {
      obj_ptr = std::make_shared<Artist>(json_obj);
   } else if (type == "album") {
      obj_ptr = std::make_shared<Album>(json_obj);
   } else if (type == "track") {
      obj_ptr = std::make_shared<Track>(json_obj);
   } else {
      throw std::invalid_argument("Invalid Spotify Type: " + type);
   }
   return obj_ptr; 
}

void SpotifyFactory::DeleteSpotify(BasicSpotify*spotify_obj){
   delete(spotify_obj);
}

// template <typename T> 
// std::shared_ptr<BasicSpotify> SpotifyFactory::CreateSpotifyObject(nlohmann::json json_obj) {
//    std::string type = json_obj["type"];
//    if (type == "artist") {
//       return std::make_shared<Artist>(json_obj);
//    } else if (type == "album") {
//       return std::make_shared<Album>(json_obj);
//    } else if (type == "track") {
//       return std::make_shared<Track>(json_obj);
//    } else {
//       throw std::invalid_argument("Invalid Spotify Type: " + type);
//    }
// }