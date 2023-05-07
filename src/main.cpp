#include "../include/SpotifyAPI.hpp"
#include "../include/ClientNetwork.h"
#include "../include/RegisteredUser.hpp"
#include "../include/SpotifyFactory.hpp"
#include "../include/Search.hpp"
#include <cstdlib>
#include <stdio.h>
#include <cctype>
#include <cstring>
#include <istream>

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
int StartGuestMode(std::string);

int main(){
   std::string client_id = "23ba501c09bd4194b3f2771c98fb5814";
   std::string client_secret = "eb80eac6f244443fae50300fc8db1479";
   ClientNetwork network = ClientNetwork();
   
   cout << "\nWelcome to Spoti-Stats!" << endl;
   DisplayHomeMenu();
   
   cout << "> ";
   int selection;
   std::string input;
   std::getline(std::cin, input);
   selection = std::stoi(input);

      /**
         MODE: User
      */
      if (selection == 1) { 
         cout << "\n\n==================";
         cout << "\nCurrent User: User";
         cout << "\n==================" << endl;
         
         StartConnection();
         
      } else if (selection == 2) { /// GUEST MODE
         cout << "\nCurrent User: Guest" << endl;
      
         SpotifyAPI spotify; 
         std::string client_id = spotify.GetClientID();
         std::string client_secret = spotify.GetClientSecret();
         std::string guest_token = spotify.get_auth_token(client_id, client_secret);
         std::cout << "Guest Token: " << guest_token << endl;
         StartGuestMode(guest_token);

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
           "[4] Find User Profile\n" <<
           "[9] USE FOR TESTING\n" <<
           "[5] Exit\n" << std::endl;
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
            // std::string user_auth_url = "https://accounts.spotify.com/en/authorize?client_id=23ba501c09bd4194b3f2771c98fb5814&response_type=code&redirect_uri=http%3A%2F%2Flocalhost%3A8888%2Fcallback&show_dialog=true&scope=user-read-private%20user-read-email%20user-modify-playback-state%20user-read-playback-position%20user-library-read%20streaming%20user-read-playback-state%20user-read-recently-played%20playlist-read-private";
            // std::string command = "open " + user_auth_url;
            // system(command.c_str());

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
   bool is_running = false;
   int selection; 
   try {
      while (!is_running){
         std::cout << "> ";
         std::string input; 
         std::getline(std::cin, input);
         selection = std::stoi(input);
         if (selection == 1) { // find a song
            /*
               https://open.spotify.com/track/6C9SwoZ5OrxcvkntgA5t8s?si=ea8187c2bfd84b86
            */
            SpotifyFactory factory;
            std::string song_id = spotify.GetSongID("Search & Rescue", token);
            std::cout << "song id: " << song_id << std::endl;


         } else if (selection == 4) {
            std::string input; 
            std::cout << "Search Username: ";
            std::cin >> input; 


         } else if (selection == 9) { // using input 9 for testing
            /* query_opt_t q_opts; 
            // In this case: query options for searching for songs given a name 
            q_opts["type"] = "track"; 
            q_opts["market"] = "US";
            q_opts["limit"] = "5"; // REMEMBER TO CONVER THIS FIELD TO AN INT */
            
            SpotifyFactory factory;
            std::string input; 
            std::cout << "Search Song Name: ";
            std::getline(std::cin, input);
            Search search;
            SearchTrack track_search(search);
            nlohmann::json songs = track_search.perform_search(input, token);
            
//            nlohmann::json songs = spotify.GetSongID(input, token);
             
             
//             SearchArtist artist_search(search);
//             nlohmann::json songs = artist_search.perform_search(input, token);
             
//             SearchAlbum album_search(search);
//             nlohmann::json songs = album_search.perform_search(input, token);
             
//             SearchPlaylist playlist_search(search);
//             nlohmann::json songs = playlist_search.perform_search(input, token);
                          
            spotify.PrintTop5("track", songs);

            // query_opt_t q_opts;
            // q_opts["type"] = "track";
            // q_opts["limit"] = "5";
            // q_opts["market"] = "US";
            // nlohmann::json top5_songs = spotify.SearchSongs(input, q_opts, token);

            // query_opt_t q_opts_album;
            // q_opts["type"] = "album";
            // q_opts["limit"] = "5";
            // q_opts["market"] = "US";
            // nlohmann::json top5_albums = spotify.SearchSongs(input, q_opts, token);
            // nlohmann::json track_data = spotify.GetSongID(input, token);

         } else {
            std::cout << "Invalid Selection" << std::endl;
            break;
         }
      }
   } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
   }
   
}
