#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include <fstream>
#include <cpr/cpr.h>

// old http://localhost:8888/callback
// new http://localhost:8080/callback



/*
   json.hpp library: https://github.com/nlohmann/json
   - allows for parsing json data in c++ 
*/

using json = nlohmann::json;

std::size_t callback(
    const char* in,
    std::size_t size,
    std::size_t num,
    std::string* out) {

   const std::size_t totalBytes(size * num);
   out->append(in, totalBytes);
   return totalBytes;
}

std::string encode_credentials(const std::string& client_id, const std::string& client_secret) {
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
std::string get_token(const std::string& client_id, const std::string& client_secret) {
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
      curl_easy_setopt(curl, CURLOPT_POST, 1L); // send request
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, auth_header.c_str())); // set the header
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "grant_type=client_credentials&scope=user-read-private%20user-read-email");
      // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "grant_type=client_credentials");
      // https://accounts.spotify.com/authorize?response_type=code&client_id=23ba501c09bd4194b3f2771c98fb5814&scope=user-read-private%20user-read-email&redirect_uri=http://localhost:8888/callback

      std::string response_string;
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

      

      CURLcode res = curl_easy_perform(curl);
      curl_easy_cleanup(curl);
      std::cout << "response string before parse: " << response_string << "\n" << std::endl;
      json response_json = json::parse(response_string);
      std::cout << "response string to json string: " << response_json << std::endl;
      std::string access_token = response_json["access_token"];
      std::cout << "access token: " << access_token << std::endl;
      return access_token;
   }
   std::cout << "SOMETHINGS NOT WORKING" << std::endl;
   return NULL;
}

/*

*/
json get_user_info(const std::string& access_token, const std::string& filename)
{
  /*  CURL* curl = curl_easy_init();

   std::string endpoint_url = "https://api.spotify.com/v1/me";
   std::string auth_header = "Authorization: Bearer " + access_token;

   curl_easy_setopt(curl, CURLOPT_URL, endpoint_url.c_str());
   curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, auth_header.c_str()));

   curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, "Content-Type: application/json"));
   curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, "Accept: application/json"));
   curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, "User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.3"));
   curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
   curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.75.0");
   curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
   curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
   curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
   curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");

   std::ofstream output_file(filename);

   std::string response_string;
   curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
   curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

   CURLcode res = curl_easy_perform(curl);
   curl_easy_cleanup(curl);

   if (res != CURLE_OK) {
      std::cerr << "Failed to retrieve user info: " << curl_easy_strerror(res) << std::endl;
      return json();
   }

   json response_json = json::parse(response_string);

   if (output_file.is_open()) {
      output_file << response_json.dump(4) << std::endl;
      output_file.close();
   }

   std::cout << response_string << std::endl;  
   return response_json; */


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

      // curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, "Content-Type: application/json"));
      // curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, auth_header.c_str()));
      // curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(NULL, "charset: utf-8")); 
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, auth_header.c_str());

      std::stringstream response_stream;
      // std::string response_string;

      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curl, CURLOPT_URL, endpoint_url.c_str());
      curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L); 
      curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "utf-8");
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_stream);
      std::cout << "RESPONSE STREAM = " << response_stream.str() << std::endl;
      // response_stream.reserve(1 * 1024 * 1024);
      // std::string response_str;
      // response_str.reserve(1 * 1024 * 1024); // try allocating 1MB of memory for the response string

      // response_str = response_stream.str();
      CURLcode res = curl_easy_perform(curl);
      json result; 
      if (res != CURLE_OK) {
         std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
         return json();
      }
      // std::ifstream file(filename);
      // file >> result;
      std::ofstream file(filename);
      file << result;
      file.close();
      
      // std::cout << "BAD ALLOC !!!!" << std::endl;   
      /**
       * ERROR: response_stream is empty
       */
      // std::cout << "RESPONSE_STREAM BEFORE PARSE = " << response_stream.str() << "\n";
      // json response = json::parse(response_stream.str());
      // std::cout << "RESPONSE_STREAM AFTER PARSE = " << response_stream.str() << "\n";

      // std::ofstream ofs(filename);
      // ofs << response;

      curl_slist_free_all(headers);
      curl_easy_cleanup(curl);   
      

      return result;
   }
   
   return NULL;
}

int main(){
   try {
      std::string client_id = "23ba501c09bd4194b3f2771c98fb5814";
      std::string client_secret = "eb80eac6f244443fae50300fc8db1479";

      std::string filename = "user_info.json";

      std::string access_token = get_token(client_id, client_secret);
      
      /**
         ERROR: error occurs in get_user_info()
      */
      json user_info = get_user_info(access_token, filename);
      
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