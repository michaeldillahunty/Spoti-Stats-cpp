#ifndef FORMAT_JSON_HPP
#define FORMAT_JSON_HPP

#include <nlohmann/json.hpp>
#include <vector> 
#include <string> 
#include <map>



class FormatJSON {
   private:
      nlohmann::json json_obj;    
   public:
      nlohmann::json FormatTrackJson();
      nlohmann::json FormatPlaylistJson();
      nlohmann::json FormatArtistJson();
      nlohmann::json FormatAlbumJson();
      nlohmann::json FormatUserProfileJson();
      void SetJsonObject(nlohmann::json obj) { json_obj = obj; }
      nlohmann::json GetJsonObject(){ return json_obj; }

      void PrintFormattedJson(std::string type, nlohmann::json json_obj);
};
#endif