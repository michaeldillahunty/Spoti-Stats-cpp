#include "../include/SpotifyAPI.hpp"
#include "../include/ClientNetwork.h"
#include "../include/RegisteredUser.hpp"
#include <cstdlib>
#include <stdio.h>
#include <cctype>
#include <cstring>

// Redirect URI: http://localhost:8888/callback
// VSCode Live Server Hosting: http://127.0.0.1:5500/index.html

// User Authorization URL:
// "https://accounts.spotify.com/authorize?client_id=YOUR_CLIENT_ID&response_type=code&redirect_uri=http://localhost:8000&scope=user-read-private%20user-read-email";
// https://accounts.spotify.com/en/authorize?client_id=23ba501c09bd4194b3f2771c98fb5814&response_type=code&redirect_uri=http://localhost:8888/callback&show_dialog=true&scope=user-read-private%20user-read-email%20user-modify-playback-state%20user-read-playback-position%20user-library-read%20streaming%20user-read-playback-state%20user-read-recently-played%20playlist-read-private
#define CLIENT_ID 23ba501c09bd4194b3f2771c98fb5814

/* 
   SPOTIFY MAIN
*/
int StartConnection();
void DisplayHomeMenu();
void DisplayGuestMenu();
void DisplayUserMenu();

int main(){
   /* SpotifyAPI spotify; 
   std::string client_id = "23ba501c09bd4194b3f2771c98fb5814";
   std::string client_secret = "eb80eac6f244443fae50300fc8db1479";
   std::string user_id = "dillahuntym";

   try {

      // std::string refresh_token = spotify.get_refresh_token();
      std::string token = spotify.get_auth_token(client_id, client_secret);
      std::cout << "Access Token: " << token << std::endl;

      std::string user_info = spotify.api_request_test(token, user_id, "user_info.json");
   } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
   } */
   std::string client_id = "23ba501c09bd4194b3f2771c98fb5814";
   std::string client_secret = "eb80eac6f244443fae50300fc8db1479";
   ClientNetwork network = ClientNetwork();
   
   cout << "\nWelcome to Spoti-Stats!" << endl;
   DisplayHomeMenu();
   
   cout << "> ";
   int selection;
   cin >> selection;
   
   

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
         DisplayGuestMenu();
         /*
            If guest mode is selected:
            - Don't need to do anything with the server
            - Display Guest options
         */

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
   cout << "[1] Login to Spotify\n" <<
           "[2] Continue as Guest\n" <<
           "[3] Exit" << endl;
}

void DisplayGuestMenu(){
   cout << "[1] Find a Song\n" <<
           "[2] Find an Album\n" <<
           "[3] Find an Artist\n" <<
           "[4] Find User Profile\n" <<
           "[5] Exit\n" << endl;
}

void DisplayUserMenu(){
   
}


int StartConnection(){
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
            std::string user_auth_url = "https://accounts.spotify.com/en/authorize?client_id=23ba501c09bd4194b3f2771c98fb5814&response_type=code&redirect_uri=http%3A%2F%2Flocalhost%3A8888%2Fcallback&show_dialog=true&scope=user-read-private%20user-read-email%20user-modify-playback-state%20user-read-playback-position%20user-library-read%20streaming%20user-read-playback-state%20user-read-recently-played%20playlist-read-private";
            std::string command = "open " + user_auth_url;
            system(command.c_str());

         } else if (redir_input == "n") {
            cout << "Valid Input - No" << endl;
         } else {
            cout << "Invalid Input" << endl;
         }

      } catch (exception& e) {
         cout << e.what() << endl;
      }
      
      /* RegisteredUser r_user; 
      string input_user, input_pass; 
      cout << "Login to Spotify: \n Username: ";
      cin >> input_user;
      cout << "\n Password: ";
      cin >> input_pass; 
      r_user.SetLogin(input_user, input_pass); */

      
   }

}