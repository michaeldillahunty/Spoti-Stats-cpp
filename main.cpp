#include "SpotifyAPI.hpp"

// old http://localhost:8888/callback
// new http://localhost:8080/callback

int main(){
   SpotifyAPI spotify; 
   std::string client_id = "23ba501c09bd4194b3f2771c98fb5814";
   std::string client_secret = "eb80eac6f244443fae50300fc8db1479";
   std::string user_id = "dillahuntym";
   std::string token = spotify.get_auth_token(client_id, client_secret);
   std::cout << "Access Token: " << token << std::endl;

   std::string user_info = spotify.api_request_test(token, user_id, "user_info.json");

   return 0;
}
