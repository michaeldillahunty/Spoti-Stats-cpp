#include "../include/ClientNetwork.h"

#define UNUSED(x) (void)(x)

bool ClientNetwork::connect_socket(){
   if ((client_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
      cout << "[Error]: Failed to create socket" << endl;
      return false;
   }
   
   sock_addrs.sin_family = AF_INET;
   sock_addrs.sin_port = htons(SERVER_PORT);
   sock_addrs.sin_addr.s_addr = INADDR_ANY;

   if (connect(client_sock_fd, (struct sockaddr*)&sock_addrs, sizeof(sock_addrs)) == -1){
      cout << "[Error]: Failed to connect client to socket" << endl;
      return false;
   }

   return true;
}

string ClientNetwork::receive_response() {
   char msg_buff[MAX_MSG];
   if (recv(client_sock_fd, msg_buff, sizeof(msg_buff), 0) < 0) {
      return ""; 
   }
   return msg_buff; 
}

bool ClientNetwork::send_msg(string msg){
   if (send(client_sock_fd, msg.c_str(), msg.length(), 0) < 0){
      cout << "[Error]: Message send failed" << endl;
      return false;
   }
   return true;
}


int ClientNetwork::login(string username, string password) {
   if (send_msg("Login " + username + " " + password)){
      string res = receive_response();
      if (res == "Login Success"){
         cout << "Successfully Logged-in" << endl;
         return 1;
      } else if (res == "Login Fail") {
         cout << "Failed to Login" << endl;
         return 0;
      } else {
         cout << "Invalid Response" << endl;
         return 0;
      }
   } else {
      cout << "[Error] Failed to send message" << endl;
      return 0;
   }
   return 0;
}

int ClientNetwork::guest(string username, string password) {
   UNUSED(username);
   UNUSED(password);
   return 0; 
}

