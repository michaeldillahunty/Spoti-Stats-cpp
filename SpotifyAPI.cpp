#include "SpotifyAPI.hpp"

std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out) {
   const std::size_t totalBytes(size * num);
   out->append(in, totalBytes);
   return totalBytes;
}

// void SpotifyAPI::set_credentials(std::string client_id, std::string client_secret){
//    _client_id = client_id;
//    _client_secret = client_secret; 
// }

// std::string SpotifyAPI::get_credentials(){
//    return encode_credentials(_client_id, _client_secret);
// }


/*
   Function to encode the registered spotify application id and secret keys
   -> returns encoded string credentials which is used to obtain the Authorization token
*/
std::string SpotifyAPI::encode_credentials(const std::string& client_id, const std::string& client_secret) {
   std::string credentials = client_id + ":" + client_secret;

   const char* b64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
   std::string encoded_credentials;

   int val = 0, valb = -6;
   for (unsigned char c : credentials){
      val = (val << 8) + c;
      valb += 8;
      while (valb >= 0){
         encoded_credentials.push_back(b64_table[(val >> valb) & 0x3F]);
         valb -= 6;
      }
   }

   if (valb > -6) {
      encoded_credentials.push_back(b64_table[((val << 8) >> (valb + 8)) & 0x3F]);
   }
   
   while (encoded_credentials.size() % 4) {
      encoded_credentials.push_back('=');
   }
   std::cout << "encoded credentials: " << encoded_credentials << std::endl;
   return encoded_credentials;
}

/*
   Function for user to authenticate access to their spotify account - get OAuth2 Token 
      (note: tokens last 1 hour (3600 seconds) -> once this expires need refresh token)
*/
std::string SpotifyAPI::get_token(const std::string& client_id, const std::string& client_secret) {
   /*
      references:
      - https://developer.spotify.com/documentation/web-api/tutorials/client-credentials-flow
   */

   CURL* curl = curl_easy_init();
   if (curl){
      // convert client credentials to base64
      std::string encoded_credentials = encode_credentials(client_id, client_secret);

      std::string auth_url = "https://accounts.spotify.com/api/token";
      std::string auth_header = "Authorization: Basic ";
      auth_header += encoded_credentials; // concatenate header and credentials

      // auth_header += "'";
      // std::string auth_header2 = "Content-Type: application/x-www-form-urlencoded";
      // auth_header += auth_header2;

      std::cout << "\nauth_header = " << auth_header << std::endl; 

      curl_easy_setopt(curl, CURLOPT_URL, auth_url.c_str()); 
      // curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8080/callback");

      curl_easy_setopt(curl, CURLOPT_POST, 1L); // send request
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, auth_header.c_str())); // set the header
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "grant_type=client_credentials&scope=user-read-private%20user-read-email&redirect_uri=http://localhost:8080/callback");
      // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "grant_type=client_credentials");
      // https://accounts.spotify.com/authorize?response_type=code&client_id=23ba501c09bd4194b3f2771c98fb5814&scope=user-read-private%20user-read-email&redirect_uri=http://localhost:8888/callback

      std::string response_string;
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

      

      CURLcode res = curl_easy_perform(curl);
      curl_easy_cleanup(curl);
      std::cout << "[Before Parse to JSON]: " << response_string << "\n" << std::endl;
      json response_json = json::parse(response_string);
      std::cout << "[Parsed to JSON String]: " << response_json << std::endl;
      std::string access_token = response_json["access_token"];
      std::cout << "[Access Token]: " << access_token << std::endl;
      return access_token;
   }
   return NULL;
}

/*
   Using the previously obtained access token, send access token to get 'user_data' (endpoint: https://api.spotify.com/v1/me)
   from Spotify Web API
*/
json SpotifyAPI::get_user_info(const std::string& access_token, const std::string& filename) {

   /**
    * MAYBE: 
    * 1) Write json response from get_token() to the file, then in get_user_info()
    *    read from the file 
   */
   CURL* curl = curl_easy_init();
   if (curl){
      std::cout << "ACCESS TOKEN IN GET_USER_INFO = " << access_token << std::endl;

      // endpoint for userdata
      std::string endpoint_url = "https://api.spotify.com/v1/me";
      std::string auth_header = "Authorization: Bearer " + access_token;
      struct curl_slist* headers = nullptr;

      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, auth_header.c_str());
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

      std::stringstream response_stream;
      std::string response_buffer;

      curl_easy_setopt(curl, CURLOPT_URL, endpoint_url.c_str());
      curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); 
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);  // Can't authenticate the certificate, so disable authentication.
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer);
      // curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "utf-8");
      // curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_stream);
      


      // response_str = response_stream.str();
      CURLcode res = curl_easy_perform(curl);
      // json result; 
      if (res != CURLE_OK) {
         std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
         return json();
      }
   
      /**
       * ERROR: response_stream is empty
       */
      // json response = json::parse(response_stream.str());
      json response = json::parse(response_buffer);
      // std::ifstream file(filename);
      // file >> result;
      std::ofstream file(filename);
      file << response;
      file.close();

      curl_slist_free_all(headers);
      curl_easy_cleanup(curl);   
      

      return response;
   }
   std::cerr << "Failed to initiate cURL" << std::endl;
   return NULL;
}