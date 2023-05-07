#ifndef SEARCH_HPP
#define SEARCH_HPP

#include "SpotifyAPI.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::client;

// helper function
nlohmann::json send_http_request(http_client* search_client, uri_builder builder, std::string auth_token);

/** Decorator Design Pattern */
struct Decorator {
   virtual nlohmann::json perform_search(std::string search_value, const std::string auth_token) = 0;
};

class Search : public Decorator {
   http_client* search_client;
   uri_builder builder;

   public:
      nlohmann::json perform_search(std::string search_value, const std::string auth_token) override;
      http_client* get_client() {
         return search_client;
      }
      uri_builder get_builder() {
         return builder;
      }
};

class SearchTrack : public Decorator {
   Search& search;

   public:
      SearchTrack(Search& s): search{s} {}

      nlohmann::json perform_search(std::string search_value, const std::string auth_token) override;
};

class SearchArtist : public Decorator {
   Search& search;

   public:
      SearchArtist(Search& s): search{s} {}

      nlohmann::json perform_search(std::string search_value, const std::string auth_token) override;
};

class SearchAlbum : public Decorator {
   Search& search;

   public:
      SearchAlbum(Search& s): search{s} {}
      
      nlohmann::json perform_search(std::string search_value, const std::string auth_token) override;
};

class SearchPlaylist : public Decorator {
   Search& search;

   public:
      SearchPlaylist(Search& s): search{s} {}

      nlohmann::json perform_search(std::string search_value, const std::string auth_token) override;
};

#endif 
