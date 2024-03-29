#include "../include/SpotifyAPI.hpp"

#define AUTHORIZE_URL "https://accounts.spotify.com/authorize"
#define REDIRECT_URI "http://localhost:8080/callback"
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace web;
using namespace web::http;
using namespace web::http::client;

std::size_t callback(const char* in, std::size_t size, std::size_t num, std::string* out) {
   const std::size_t totalBytes(size * num);
   out->append(in, totalBytes);
   return totalBytes;
}


/*
 End of Decorator Design Pattern
 */

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
   // std::cout << "encoded credentials: " << encoded_credentials << std::endl;
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
      nlohmann::json res_json = nlohmann::json::parse(response_buff);
      file << res_json; 
      file.close();
      std::string access_token = res_json["access_token"];
      // std::cout << "ACCESS TOKEN: " << access_token << std::endl;
      return access_token;
   }
   curl_global_cleanup();
   return NULL;
}

std::string SpotifyAPI::get_auth_header(const std::string& access_token){
   std::string auth_header = "Authorization: Bearer " + access_token;
   return auth_header;
}

/*
   Example function for sending a public-scoped request to Spotify API 
*/
nlohmann::json SpotifyAPI::api_request_test(const std::string& access_token, const std::string& user_id, const std::string& filename){
   CURL*curl = curl_easy_init();
   CURLcode res; 
   if (curl) {
      std::string auth_header = get_auth_header(access_token);
      std::string endpoint_url = "https://api.spotify.com/v1/users/";
      endpoint_url += user_id; 
      struct curl_slist* headers = nullptr; 
      headers = curl_slist_append(headers, auth_header.c_str());

      std::string res_buff;
      curl_easy_setopt(curl, CURLOPT_URL, endpoint_url.c_str());
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

/**
 * Sending HTTP GET Request using libcurl 
 * 
*/
nlohmann::json SpotifyAPI::SpotifyCURL(std::string endpoint, std::string auth_token){
   CURL*curl = curl_easy_init();
   CURLcode res; 
   if (curl) {
      std::string auth_header = get_auth_header(auth_token);
      std::string endpoint_url = "https://api.spotify.com";
      endpoint_url += endpoint; 
      std::cout << "ENDPOINT URL: " << endpoint_url << std::endl;

      struct curl_slist* headers = nullptr; 
      headers = curl_slist_append(headers, auth_header.c_str());
      std::string res_buff;
      curl_easy_setopt(curl, CURLOPT_URL, endpoint_url.c_str());
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res_buff);

      res = curl_easy_perform(curl);
      if (res != CURLE_OK){
         std::cerr << "Failed to send Post Request: " << curl_easy_strerror(res) << std::endl; 
         return nullptr;
      }
      
      // std::cout << res_buff << std::endl;
      curl_easy_cleanup(curl);

      std::ofstream file(GUEST_OUTPUT_FILE);
      file << res_buff; 
      file.close();

      return res_buff;
   }
   return nullptr;
}

nlohmann::json SpotifyAPI::GetPublicUser(std::string username, std::string auth_token){
   return SpotifyCURL("/v1/users/" + username, auth_token);
}

std::string SpotifyAPI::GetSongID(std::string song, const std::string auth_token){
   std::cout << "GIVEN SONG: " << song << std::endl;
   std::string encoded_song_name = "";
   for (const auto& c : song) {
      if (c == ' ') {
         encoded_song_name += "%20";
      } else {
         encoded_song_name += c;
      }
   }
   
   // Creating the HTTP GET Request
   http_client client(U("https://api.spotify.com/v1/search"));
   uri_builder builder;
   builder.append_query(U("q"), utility::conversions::to_utf8string(encoded_song_name));
   builder.append_query(U("type"), U("track"));
   builder.append_query(U("limit"), 5);
   builder.append_query(U("market"), U("US"));
   web::http::http_request req(methods::GET);
   req.set_request_uri(builder.to_uri());
   req.headers().add(U("Authorization"), utility::conversions::to_utf8string("Bearer " + auth_token));

   // Handling the response from the Spotify API
   http_response response = client.request(req).get();
   nlohmann::json json_obj;
   if (response.status_code() == status_codes::OK) {
      json_obj = nlohmann::json::parse(response.extract_utf8string().get());
      json_obj.erase("available_markets");
   } else {
      throw std::runtime_error("Failed to get song id");
   }
   
   // Parse the song ID from the JSON object
   std::string song_id;
   if (json_obj.contains("tracks") && json_obj["tracks"].contains("items")) {
      auto tracks = json_obj["tracks"]["items"];
      if (!tracks.empty()) {
         song_id = tracks[0]["id"];
      }
   }
   
   if (song_id.empty()) {
      throw std::runtime_error("Failed to get song id");
   }

   return json_obj; 
}


/**
 * Sending HTTP GET Request using cpprestsdk
 * 
*/
nlohmann::json SpotifyAPI::SearchSongs(std::string song_name, query_opt_t options, std::string auth_token){
   // encode song name to HTTP format
   std::string encoded_song_name = "";
   for (const auto& c : song_name) {
      if (c == ' ') {
         encoded_song_name += "%20";
      } else {
         encoded_song_name += c;
      }
   }

   // Create HTTP client and request URI
   std::string endpoint_uri = "https://api.spotify.com/v1/search";
   http_client client(U(endpoint_uri));
   std::cout << "ENDPOINT URI: " << endpoint_uri << std::endl;
   uri_builder builder;

   std::string q_type = options.at("type");
   int q_limit = stoi(options.at("limit"));
   std::string q_market = options.at("market");
   
   // specify query 'q' and append the HTTP encoded song_name
   builder.append_query(U("q"), utility::conversions::to_utf8string(song_name)); 
   builder.append_query(U("type"), U(q_type));
   builder.append_query(U("limit"), q_limit); // only return the top 5 tracks with the given name 
   builder.append_query(U("market"), U(q_market));  // Only search in US market
   
   web::http::http_request req(methods::GET);
   req.set_request_uri(builder.to_uri());
   req.headers().add(U("Authorization"), utility::conversions::to_utf8string("Bearer " + auth_token));

   // Send HTTP request and parse JSON response
   http_response response = client.request(req).get();
   nlohmann::json json_obj;
   if (response.status_code() == status_codes::OK) {
      json_obj = nlohmann::json::parse(response.extract_utf8string().get());
      json_obj.erase("available_markets");
   } else {
      throw std::runtime_error("Failed to get song(s)");
   }

   std::string artist_name1 = json_obj["tracks"]["items"][0]["artists"][0]["name"]; // getting the name of the first artist from the first track

   return json_obj;
}

void SpotifyAPI::PrintTop5(std::string type, nlohmann::json json_obj) {
   /* Text Formatting: 
      - \033[1m escape code for bold text
      - \033[32m sets the color to green
      - \033[0m escape code resets the text format to the default
   */

   if (type == "track") {
      int i = 1;
      for (const auto& track : json_obj["tracks"]["items"]) {
         std::cout << "\033[1m\033[32mTrack " << i << " Name: " << "\033[0m" << track["name"] << std::endl;
         std::cout << "  Artist(s): ";
         bool first_artist = true;
         for (const auto& artist : track["artists"]) {
            std::string artist_name = artist["name"];
            if (!first_artist)
               std::cout << ", ";
            std::cout << artist_name;
            first_artist = false;
         }
         i++;
         std::cout << "\n" << std::endl;
      }

   } else if (type == "album"){
      int i = 1; 
      for (const auto& album : json_obj["albums"]["items"]){
         std::cout << "\033[1m\033[32m" << i << ") Album: " << "\033[0m" << album["name"] << std::endl;
         std::cout << "    by: ";
         bool first_artist = true;
         for (const auto& artist : album["artists"]) {
         std::string artist_name = artist["name"];
            if (!first_artist)
               std::cout << ", ";
            std::cout << artist_name;
            first_artist = false;
         }
         i++;
         std::cout << "\n" << std::endl;
      }

   } else if (type == "artist") {
      int i = 1; 
      for (const auto& artist : json_obj["artists"]["items"]){
         std::cout << "\033[1m\033[32m" << i << ") Artist Name: " << "\033[0m" << artist["name"] << std::endl;
         std::cout << std::endl;
         i++;
      }

   } else if (type == "playlist") {
      int i = 1; 
      for (const auto& playlist : json_obj["playlists"]["items"]){
         std::cout << "\033[1m\033[32m" << i << ") Playlist: " << "\033[0m" << playlist["name"] << std::endl;
         std::cout << "    by: " << playlist["owner"]["display_name"] << "\n" << std::endl;
         bool first = true;
         if (!first)
            std::cout << ", ";
         first = false;
         i++;
         std::cout << std::endl;
      }

   } else if (type == "user") {
      int i = 1; 
      // for (const auto& user : json_obj["users"]["items"]){
         std::cout << "\033[1m\033[32m" << i << ") User: " << "\033[0m" << json_obj["display_name"] << std::endl;
         std::cout << "    profile link: " << json_obj["external_urls"]["spotify"] << std::endl;
         i++;
         std::cout << std::endl;
      // }
   }
}

/*
   Function returns a JSON object for a given songID
*/
nlohmann::json SpotifyAPI::GetSong(std::string songID, std::string auth_token){
   // creating the query to send
   http_client client(U("https://api.spotify.com/v1/tracks/" + songID)); 
   web::http::http_request req(methods::GET);
   req.headers().add(U("Authorization"), utility::conversions::to_utf8string("Bearer " + auth_token));
   http_response response = client.request(req).get();

   // check for valid status code and parse response to json object if OK
   nlohmann::json json_obj;
   if (response.status_code() == status_codes::OK) {
      json_obj = nlohmann::json::parse(response.extract_utf8string().get());
      json_obj.erase("available_markets");
   } else {
      throw std::runtime_error("Failed to get song details");
   }
   return json_obj;
}


/*
   Function for User Level Authorization with the Spotify API 
*/
std::string SpotifyAPI::request_authorization(){
   /**
    * PROBLEMS:
    * (1) Authorization URL is working, but the redirect is not 
    *    - MAYBE: need a HTTP server library 
   */
   // ClientNetwork network = ClientNetwork();
   client_id = GetClientID();
   client_secret = GetClientSecret();
   std::string url = AUTHORIZE_URL;
   url += "?client_id=" + client_id;
   url += "&response_type=code";
   std::string redirect_uri = REDIRECT_URI;
   url += "&redirect_uri=" + redirect_uri;

    std::string auth_token = get_auth_token(client_id, client_secret);
    http_client client(U(url));
    web::http::http_request req(methods::GET);
    req.headers().add(U("Authorization"), utility::conversions::to_utf8string("Bearer " + auth_token));
    http_response response = client.request(req).get();

    /** ERROR: "provided uri is invalid: ... */
    std::cout << "\nAUTHORIZATION RESPONSE:\n" << response.to_string() << std::endl;

    // check for valid status code and parse response to json object if OK
    nlohmann::json json_obj;
    if (response.status_code() == status_codes::OK) {
        std::cout << "STATUS CODE: OK" << std::endl;
        url += "&show_dialog=true";
        url += "&scope=user-read-private user-read-email user-modify-playback-state user-read-playback-position user-library-read streaming user-read-playback-state%20user-read-recently-played playlist-read-private";
        std::string command = "open \"" + url + "\"";
        system(command.c_str());
        json_obj = nlohmann::json::parse(response.extract_utf8string().get());
    } else {
       throw std::runtime_error("Failed to Authorize");
    }
    
    return json_obj;
}
