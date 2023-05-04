#include "../include/ClientNetwork.h"

#define UNUSED(x) (void)(x)

bool ClientNetwork::connect_socket(){
   if ((client_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
      std::cout << "[Error]: Failed to create socket" << std::endl;
      return false;
   }
   
   sock_addrs.sin_family = AF_INET;
   sock_addrs.sin_port = htons(SERVER_PORT);
   sock_addrs.sin_addr.s_addr = INADDR_ANY;

   if (connect(client_sock_fd, (struct sockaddr*)&sock_addrs, sizeof(sock_addrs)) == -1){
      std::cout << "[Error]: Failed to connect client to socket" << std::endl;
      return false;
   }

   return true;
}

std::string ClientNetwork::receive_response() {
   char msg_buff[MAX_MSG_CLIENT];
   if (recv(client_sock_fd, msg_buff, sizeof(msg_buff), 0) < 0) {
      return ""; 
   }
   return msg_buff; 
}

bool ClientNetwork::send_msg(std::string msg){
   if (send(client_sock_fd, msg.c_str(), msg.length(), 0) < 0){
      std::cout << "[Error]: Message send failed" << std::endl;
      return false;
   }
   return true;
}


int ClientNetwork::login(std::string username, std::string password) {
   if (send_msg("Login " + username + " " + password)){
      std::string res = receive_response();
      if (res == "Login Success"){
         std::cout << "Successfully Logged-in" << std::endl;
         return 1;
      } else if (res == "Login Fail") {
         std::cout << "Failed to Login" << std::endl;
         return 0;
      } else {
         std::cout << "Invalid Response" << std::endl;
         return 0;
      }
   } else {
      std::cout << "[Error] Failed to send message" << std::endl;
      return 0;
   }
   return 0;
}

int ClientNetwork::guest(std::string username, std::string password) {
   UNUSED(username);
   UNUSED(password);
   return 0; 
}

