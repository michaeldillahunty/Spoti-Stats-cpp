#include "../include/SpotifyFactory.hpp"

std::shared_ptr<BasicSpotify> SpotifyFactory::CreateSpotifyObject(nlohmann::json json_obj) {
   std::string type = json_obj["type"];
   if (type == "artist") {
      return std::make_shared<Artist>(json_obj);
   } else if (type == "album") {
      return std::make_shared<Album>(json_obj);
   } else if (type == "track") {
      return std::make_shared<Track>(json_obj);
   } else {
      throw std::invalid_argument("Invalid Spotify Type: " + type);
   }
}