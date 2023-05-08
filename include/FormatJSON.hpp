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
      std::string FormatTrackJson();
      std::string FormatPlaylistJson();
      std::string FormatArtistJson();
      std::string FormatAlbumJson();
      std::string FormatUserProfileJson();
      nlohmann::json GetJsonObject(){ return json_obj; }

      void PrintFormattedJson(std::string type, nlohmann::json json_obj);
};
#endif