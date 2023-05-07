#ifndef SPOTIFY_FACTORY_HPP
#define SPOTIFY_FACTORY_HPP

#include "../src/models/BasicSpotify.h"
#include "../src/models/Artist.h"
#include "../src/models/Track.h"
#include "../src/models/Album.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <nlohmann/json.hpp>


class SpotifyFactory {

   public:
      template<typename T> 
      static std::shared_ptr<T> CreateSpotifyObject(nlohmann::json json_obj);
      static void DeleteSpotify(BasicSpotify*spotify_obj);

      static BasicSpotify*CreateObject(const nlohmann::json json_obj);
};


#endif 