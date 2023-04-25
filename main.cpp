#include "SpotifyAPI.hpp"
// #include "utils/json.h"
// #include "utils/CurlException.h"
// #include "utils/CurlUtils.h"




// old http://localhost:8888/callback
// new http://localhost:8080/callback

/*
   json.hpp library: https://github.com/nlohmann/json
   - allows for parsing json data in c++ 
*/

int main(){

   try {
      SpotifyAPI spotify; 
      std::string client_id = "23ba501c09bd4194b3f2771c98fb5814";
      std::string client_secret = "eb80eac6f244443fae50300fc8db1479";

      std::string filename = "user_info.json";

      std::string access_token = spotify.get_token(client_id, client_secret);
      
      /**
         ERROR: error occurs in get_user_info()
      */
      json user_info = spotify.get_user_info(access_token, filename);
      
      if (!user_info.is_null()) {
         std::cout << "User ID: " << user_info["id"] << std::endl;
         std::cout << "Display name: " << user_info["display_name"] << std::endl;
      } else {
         std::cout << "Error: Could not retrieve user information" << std::endl;
      }
   } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
   }
   
}



/* int main() {
  // Initialize libcurl
  curl_global_init(CURL_GLOBAL_DEFAULT);
  
  // Set up cpr::Url and cpr::Header for the Spotify API endpoint
  cpr::Url url("https://api.spotify.com/v1/me");
  cpr::Header headers{{"Authorization", "Bearer <insert your access token here>"}};
  
  // Send the GET request using cpr::Get and retrieve the response
  auto response = cpr::Get(url, headers);
  
  // Check if the request was successful
  if (response.status_code == 200) {
    // Parse the response JSON using nlohmann/json
    json j = json::parse(response.text);
    
    // Save the JSON data to a file
    std::ofstream file("spotify_data.txt");
    file << j.dump(4); // Use 4 spaces for indentation
    file.close();
    
    // Print out the username
    std::cout << "Username: " << j["display_name"] << std::endl;
  } else {
    std::cerr << "Error: " << response.status_code << std::endl;
  }
  
  // Clean up libcurl
  curl_global_cleanup();
  
  return 0;
} */
   