#include "../include/SpotifyAPI.hpp"

std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out) {
   const std::size_t totalBytes(size * num);
   out->append(in, totalBytes);
   return totalBytes;
}

/** 
 * DESCRIPTION: Function that encodes the client_id and client_secret into a base 64 string 
 *    - Spotify's Web API requires base64 encoding for api calls
 * 
 * \param client_id - the Client ID associated with the registered Spotify app on Spotify's developer site
 * \param client_secret - the Client Secret associated with the registered Spotify app on Spotify's developer site
 * \return string of base64 encoded credentials
*/
std::string SpotifyAPI::encode_credentials(const std::string& client_id, const std::string& client_secret){
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

/**
 * Function that gets the required Access Token in order to make request to Spotify API 
 *    - Specifies the 'scopes' allowed
*/
std::string SpotifyAPI::get_auth_token(const std::string& client_id, const std::string& client_secret){
   CURL*curl; 
   CURLcode res;
   curl_global_init( CURL_GLOBAL_ALL );

   curl = curl_easy_init();
   if (curl) {
      std::string encoded_creds;
      encoded_creds = encode_credentials(client_id, client_secret);
      
      std::string auth_url = "https://accounts.spotify.com/api/token"; 
      
      struct curl_slist* headers = nullptr; // linked list 
      std::string auth_header = "Authorization: Basic ";
      auth_header += encoded_creds;
      headers = curl_slist_append(headers, auth_header.c_str());
      headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

      // data string can also contain the scopes
      std::string data;
      data = "grant_type=client_credentials&scope=user-read-private%20user-read-email";
      
      std::string response_buff; 
      curl_easy_setopt(curl, CURLOPT_URL, auth_url.c_str()); // url to send the POST request 
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str()); // setting the POST data 
      curl_easy_setopt(curl, CURLOPT_POST, 1L); // HTTP Method set to POST
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buff);

      res = curl_easy_perform(curl); // send the POST/GET Request
      if (res != CURLE_OK){
         std::cerr << "Failed to send Post Request: " << curl_easy_strerror(res) << std::endl; 
         return NULL;
      }
      curl_easy_cleanup(curl);

      std::ofstream file("auth_token.json"); 
      json res_json = json::parse(response_buff);
      file << res_json; 
      file.close();
      std::string access_token = res_json["access_token"];
      return access_token;
   }
   curl_global_cleanup();
   return NULL;
}

/* void SpotifyAPI::save_refresh_token(const std::string& refresh_token) { // refresh token won't be modified inside of the function so make it const
   std::ofstream of("refresh_token.json");
   of << refresh_token;
   of.close();
}

std::string SpotifyAPI::get_refresh_token(){
   std::ifstream ifs("refresh_token.json");
   std::string refresh_token;
   if (ifs.is_open()){
      std::getline(ifs, refresh_token);
      ifs.close();
   }
   return refresh_token;
} */

std::string SpotifyAPI::get_auth_header(const std::string& access_token){
   std::string auth_header = "Authorization: Bearer " + access_token;
   return auth_header;
}

json SpotifyAPI::api_request_test(const std::string& access_token, const std::string& user_id, const std::string& filename){
   CURL*curl = curl_easy_init();
   CURLcode res; 
   if (curl) {
      std::string auth_header = get_auth_header(access_token);
      std::string endpoint_url2 = "https://api.spotify.com/v1/me";
      std::string endpoint_url = "https://api.spotify.com/v1/users/";
      endpoint_url += user_id; 
      struct curl_slist* headers = nullptr; 
      headers = curl_slist_append(headers, auth_header.c_str());

      std::string res_buff;
      curl_easy_setopt(curl, CURLOPT_URL, endpoint_url.c_str());
      // libcurl automatically assumes requests are GET requests, don't need to specify HTTPGET unless we are wanting to be explicit
      // curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res_buff);

      res = curl_easy_perform(curl);
      if (res != CURLE_OK){
         std::cerr << "Failed to send Post Request: " << curl_easy_strerror(res) << std::endl; 
         return nullptr;
      }
      
      std::cout << res_buff << std::endl;
      curl_easy_cleanup(curl);

      // json res_json = json::parse(res_buff); // parses json into a string
      std::ofstream file(filename);
      file << res_buff; 
      file.close();

      return res_buff;
   }
   return nullptr;
}
