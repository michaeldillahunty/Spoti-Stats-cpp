#ifndef DETAILEDSEARCH_HPP
#define DETAILEDSEARCH_HPP

#include "SpotifyAPI.hpp"

/*
 
This class will be used once the user selects a specific item to have more detail displayed.
 
 */
class DetailedSearch {
    public:
        nlohmann::json detailed_search(std::string endpoint, std::string id, std::string auth_token);
};

#endif
