#include "BasicSpotify.h"

BasicSpotify::BasicSpotify(nlohmann::json json) {
   id = json["id"];
   for (auto it = json["external_urls"].begin(); it != json["external_urls"].end(); ++it)
      external_urls[it.key()] = it.value();
   name = json["name"];
   type = json["type"];
}