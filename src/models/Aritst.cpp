#include "Artist.hpp"

Artist::Artist(nlohmann::json artist_json) {
    for (auto it = artist_json["external_urls"].begin(); it != artist_json["external_urls"].end(); ++it)
        external_urls[it.key()] = it.value();

    href = artist_json["href"];
    id = artist_json["id"];
    name = artist_json["name"];
    type = artist_json["type"];
    uri = artist_json["uri"];
}

std::map<std::string, std::string> Artist::GetExternalURLs() const {
    return external_urls;
}

std::string Artist::GetHref() const {
   return href;
}

std::string Artist::GetID() const {
   return id; 
}

std::string Artist::GetName() const {
   return name;
}

std::string Artist::GetType() const {
   return type;
}

std::string Artist::GetUri() const {
   return uri;
}