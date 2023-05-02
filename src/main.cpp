#include "../include/SpotifyAPI.hpp"
#include "../include/ClientNetwork.h"

// old http://localhost:8888/callback
// new http://localhost:8080/callback

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
   
   ClientNetwork network = ClientNetwork();
   
   cout << "\nWelcome to Spoti-Stats!" << endl;
   DisplayHomeMenu();
   
   cout << "> ";
   int selection;
   cin >> selection;
   bool while1 = true;
   bool connection_status = false;
   while (while1) {
      /**
         MODE: User
      */
      if (selection == 1) { 
         cout << "\n\n==================";
         cout << "\nCurrent User: User";
         cout << "\n==================" << endl;
         while (!connection_status){
            connection_status = network.establish_connection();
            if (!connection_status){
               cout << "Failed to connect to server - Retrying..." << endl;
               sleep(3);
            }
         }
         string response;
         if ((response = network.receive_response()) == ""){
            cout << "Could not retrieve message from Server" << endl;
         } else {
            cout << response;
         }
         
   
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
         break;
      }
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


int StartConnection(){
   ClientNetwork network = ClientNetwork(); 
   bool connection_status = false;
   bool msg_received = false;

   while (true) {
      msg_received = false;
      while (!connection_status) {
         connection_status = network.establish_connection();
         if (!connection_status) {
            cout << "Connection error - retrying..." << endl;
            sleep(3);
         }
      }
      while (!msg_received) {
         cout << "Waiting for connection..." << endl;
         string response = network.receive_response();
         if (response != "") {
            cout << "Response Message: " << response << endl;
            msg_received = true;
         } else {
            connection_status = false;
            msg_received = false; 
         }
      }
   }
}