#include "../include/SpotifyAPI.hpp"
#include "../include/ClientNetwork.h"
#include "../include/RegisteredUser.hpp"
#include "../include/SpotifyFactory.hpp"
#include "../src/models/BasicSpotify.h"
#include "../include/Search.hpp"
#include "../include/DetailedSearch.hpp"
#include "../include/FormatJSON.hpp"
#include <cstdlib>
#include <stdio.h>
#include <cctype>
#include <cstring>
#include <istream>
#include <nlohmann/json.hpp>

// Redirect URI: http://localhost:8888/callback
// VSCode Live Server Hosting: http://127.0.0.1:5500/index.html

// User Authorization URL:
// "https://accounts.spotify.com/authorize?client_id=YOUR_CLIENT_ID&response_type=code&redirect_uri=http://localhost:8000&scope=user-read-private%20user-read-email";
// https://accounts.spotify.com/en/authorize?client_id=23ba501c09bd4194b3f2771c98fb5814&response_type=code&redirect_uri=http://localhost:8888/callback&show_dialog=true&scope=user-read-private%20user-read-email%20user-modify-playback-state%20user-read-playback-position%20user-library-read%20streaming%20user-read-playback-state%20user-read-recently-played%20playlist-read-private
#define CLIENT_ID "23ba501c09bd4194b3f2771c98fb5814"

/* 
   SPOTIFY MAIN
*/
int StartConnection();
void DisplayHomeMenu();
void DisplayGuestMenu();
void DisplayUserMenu();
void PrintDetailedJson(std::string type, nlohmann::json formatted_json);
int StartGuestMode(std::string);
nlohmann::json search_helper(std::string, std::string, Search&, const std::string&);

int main(){
   std::string client_id = "23ba501c09bd4194b3f2771c98fb5814";
   std::string client_secret = "eb80eac6f244443fae50300fc8db1479";
   // ClientNetwork network = ClientNetwork();
   
   // cout << "\nWelcome to Spoti-Stats!" << endl;
   cout << "\033[1m\033[32m"
         " _____             _   _        _____ _        _       \n"
         "/  ___|           | | (_)      /  ___| |      | |      \n"
         "\\ `--. _ __   ___ | |_ _ ______\\ `--.| |_ __ _| |_ ___ \n"
         " `--. \\ '_ \\ / _ \\| __| |______|`--. \\ __/ _` | __/ __|\n"
         "/\\__/ / |_) | (_) | |_| |      /\\__/ / || (_| | |_\\__ \\ \n"
         "\\____/| .__/ \\___/ \\__|_|      \\____/ \\__\\__,_|\\__|___/\n"
         "      | |                                              \n"
         "      |_|                                              \n"
         "\033[0m";
   
   DisplayHomeMenu();
   
   cout << "> ";
   int selection;
   std::string input;
   std::getline(std::cin, input);
   selection = std::stoi(input);

      /**
       * MODE: User
      */
      if (selection == 1) { 
         cout << "\n\n==================";
         cout << "\nCurrent User: <User>";
         cout << "\n==================" << endl;
         
         StartConnection();
      
      /**
       * MODE: Guest
      */
      } else if (selection == 2) { /// GUEST MODE
         cout << "================" << endl;
         cout << "\033[1m\033[32mCurrent Mode: Guest\033[0m" << endl;
         cout << "================" << endl;
         SpotifyAPI spotify; 
         std::string client_id = spotify.GetClientID();
         std::string client_secret = spotify.GetClientSecret();
         std::string guest_token = spotify.get_auth_token(client_id, client_secret);
         // std::cout << "Guest Token: " << guest_token << endl;
         bool is_running = false; 
         while (!is_running){
            StartGuestMode(guest_token);
         }

      } else if (selection == 3) {
         cout << "Exiting..." << endl;
         exit(EXIT_SUCCESS);    

      } else {
         cout << "Invalid Input!\nPlease enter a value between 1-3" << endl;
         DisplayHomeMenu();
         cout << "> ";
         cin >> selection;

      }

   return 0;
}

void DisplayHomeMenu(){
   std::cout << "[1] Login to Spotify\n" <<
           "[2] Continue as Guest\n" <<
           "[3] Exit" << std::endl;
}

void DisplayGuestMenu(){
   std::cout << "[1] Find a Song\n" <<
           "[2] Find an Album\n" <<
           "[3] Find an Artist\n" <<
           "[4] Find a Playlist\n"
           "[5] Find a User's Profile\n" <<
           "[6] Exit\n" << std::endl;
}

void DisplayUserMenu(){
   std::cout << "CURRENTLY NOT WORKING" << std::endl;
}



/** 
 * Function used for User-Authentication/non-public scoped api requests 
 * 
*/
int StartConnection(){
   SpotifyAPI spotify;
   bool connection_status = false;
   ClientNetwork network = ClientNetwork(); 

   while (!connection_status){ // while there is no connection
      connection_status = network.connect_socket();
      if (!connection_status){ // if the connection failed
         cout << "Failed to connect to server - Retrying..." << endl;
         sleep(3);
      }
   }

   string response = network.receive_response();
   if (response == ""){ // blank response
      cout << "Could not retrieve message from Server" << endl;
   } else {
      cout << response << endl;      
   }

   while(1){  
      string redir_input; 
      cout << "Redirect to Spotify login? (y/n)" << endl;
      cin >> redir_input; 
      try {
         if (redir_input == "y") {
            cout << "Redirecting to Spotify Page..." << endl;
            spotify.request_authorization();
         } else if (redir_input == "n") {
            cout << "Valid Input - No" << endl;
         } else {
            cout << "Invalid Input" << endl;
         }
      } catch (exception& e) {
         cout << e.what() << endl;
      }  
   }
}



// template<>
// std::shared_ptr<Track> SpotifyFactory::CreateSpotifyObject<Track>(nlohmann::json json_obj) {
//     return std::make_shared<Track>(json_obj);
// }

int StartGuestMode(std::string token){
   DisplayGuestMenu();
   SpotifyAPI spotify; 
   DetailedSearch detailed_search;
   // bool is_running = false;
   int selection; 
   try {
      std::cout << "> ";
      // while (!is_running){
         std::string input; 
         std::getline(std::cin, input);
         selection = std::stoi(input);
      
         /**
          * SEARCH SONG
         */
         if (selection == 1) { 
            Search search;       
            nlohmann::json track = search_helper("track", "Search Track: ", search, token);
            spotify.PrintTop5("track", track);
            input.clear();
             
            // detailed search
            std::cout << "Select a track to learn more about it.\n> ";
            std::getline(std::cin, input);
            selection = std::stoi(input);
            std::string track_id = track["tracks"]["items"][selection-1]["id"];
            nlohmann::json detailed_track = detailed_search.detailed_search("v1/tracks/", track_id, token);
            // std::cout << detailed_track << std::endl;
            

         /**
          * SEARCH ALBUMS
         */
         } else if (selection == 2) {
            Search search;       
            nlohmann::json album = search_helper("album", "Search Album: ", search, token);
            spotify.PrintTop5("album", album);
            input.clear();
             
            // detailed search
            // std::cout << "Select an album to learn more about it.\n> ";
            // std::getline(std::cin, input);
            // selection = std::stoi(input);
            // std::string album_id = album["albums"]["items"][selection-1]["id"];
            // nlohmann::json detailed_album = detailed_search.detailed_search("v1/albums/", album_id, token);
         
         /**
          * SEARCH ARTISTS
         */
         } else if (selection == 3) {
            Search search;       
            nlohmann::json artist = search_helper("artist", "Search Artist: ", search, token);
            spotify.PrintTop5("artist", artist);
             
            // detailed search
            // std::cout << "Select an artist to learn more about them.\n> ";
            // std::getline(std::cin, input);
            // selection = std::stoi(input);
            // std::string artist_id = artist["artists"]["items"][selection-1]["id"];
            // nlohmann::json detailed_artist = detailed_search.detailed_search("v1/artists/", artist_id, token);

         /** 
          * SEARCH PLAYLISTS
         */
         } else if (selection == 4) { // playlist
            Search search;       
            nlohmann::json playlist = search_helper("playlist", "Search Playlist: ", search, token);
            // std::cout << playlist.dump(4) << std::endl;
            spotify.PrintTop5("playlist", playlist);
             
            // detailed search
            // std::cout << "Select a playlist to learn more about it.\n> ";
            // std::getline(std::cin, input);
            // selection = std::stoi(input);
            // std::string playlist_id = playlist["playlists"]["items"][selection-1]["id"];
            // nlohmann::json detailed_playlist = detailed_search.detailed_search("v1/playlists/", playlist_id, token);
            // detailed_playlist.erase("available_markets");
            // std::cout << detailed_playlist.dump(4) << std::endl;
            // // PrintDetailedJson(detailed_playlist);
            // // FormatJSON format; 
            // // format.SetJsonObject(detailed_playlist);
            // // nlohmann::json formatted = format.FormatPlaylistJson();
            // // std::cout << formatted.dump(4) << std::endl;
            // // format.PrintFormattedJson("playlist", formatted);

         /**
          * SEARCH USER PROFILES
         */
         } else if (selection == 5) { 
            Search search; 
            nlohmann::json user_profile = search_helper("user", "Search Username: ", search, token);
            spotify.PrintTop5("user", user_profile);
         
         /**
          * EXIT
         */
         } else if (selection == 6) { 
            std::cout << "Exiting..." << std::endl;
            exit(0);
         
         /** @def 
          * TESTING
         */ 
         } else if (selection == 9) {

         } else {
            std::cout << "Invalid Selection" << std::endl;
         }
   } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
   }
   return 0;
}

nlohmann::json search_helper(std::string type, std::string prompt, Search& search_obj, const std::string& token) {
   std::string input;
   std::cout << prompt;
   std::getline(std::cin, input);
   nlohmann::json result;
   if (type == "track") {
      SearchTrack track_search(search_obj);
      result = track_search.perform_search(input, token);
      input.clear();
   } else if (type == "album") {
      SearchAlbum album_search(search_obj);
      result = album_search.perform_search(input, token);
      input.clear();
   } else if (type == "artist") {
      SearchArtist artist_search(search_obj);
      result = artist_search.perform_search(input, token);
      input.clear();
   } else if (type == "playlist") {
      SearchPlaylist playlist_search(search_obj);
      result = playlist_search.perform_search(input, token); 
      input.clear();
   } else if (type == "user") {
      SearchPublicUser user_search(search_obj);
      result = user_search.perform_search(input, token);
      input.clear();
   }
   return result;
}


// void PrintDetailedJson(nlohmann::json formatted_json){
//    for (const auto& [key, value] : formatted_json.items()) {
//       std::cout << "\033[1m\033[32m" << key << ":\033[0m ";
//       if (value.is_string() || value.is_number() || value.is_boolean()) {
//          std::cout << value.dump() << std::endl;
//       } else if (value.is_array()) {
//          for (const auto& elem : value) {
//             std::cout << "- " << elem.dump() << std::endl;
//          }
//       } else if (value.is_object()) {
//          for (const auto& [obj_key, obj_value] : value.items()) {
//             std::cout << "  \033[1m" << obj_key << ":\033[0m " << obj_value.dump() << std::endl;
//          }
//       } else {
//          std::cout << "Invalid JSON type" << std::endl;
//       }
//    }
// }