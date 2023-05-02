#include "../include/ServerNetwork.h"
#define UNUSED(x) (void)(x)

bool ServerNetwork::establish_connection() {
   if ((server_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      cerr << "[Error]: Failed to initialize server socket" << endl;
      return false; 
   }
   
   int optval = 1; 
   if (setsockopt(server_sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))) {
      cout << "[Error]: Unable to reuse Port #" << SERVER_PORT << endl;
      return false;
   }

   sock_addrs.sin_family = AF_INET;
   sock_addrs.sin_port = htons(SERVER_PORT);
   sock_addrs.sin_addr.s_addr = INADDR_ANY;

   if (::bind(server_sock_fd, (struct sockaddr*)&sock_addrs, sizeof(sock_addrs)) < 0){
      cout << "[Error]: Failed to bind address to socket" << endl;
      return false;
   }

   if (listen(server_sock_fd, MAX_PENDING) < 0) {
      cout << "Error occured while listening for connection" << endl;
      return false;
   }

   cout << "Server Successfully Connected to Socket - Waiting for Client to Connect" << endl;
   return true;
}

int ServerNetwork::accept_connection() {
   int size = sizeof(sock_addrs);
   if ((curr_socket = accept(server_sock_fd, (struct sockaddr*)&sock_addrs, (socklen_t*)&size)) == -1) {
      cout << "[Error]: Could not accept connection" << endl;
      return curr_socket;
   } else {
      cout << "Successfully accepted socket connection" << endl;
      return curr_socket;
   }
}

bool ServerNetwork::send_msg(int socket, string msg) {
   char buffer[MAX_MSG];
   strcpy(buffer, msg.c_str());
   if (send(socket, buffer, sizeof(buffer), 0) < 0) {
      cout << "[Error]: Failed to send message" << endl;
      return false;
   }
   return true; 
}

string ServerNetwork::recieve_msg(int socket) {
   char buffer[MAX_MSG];
   if (recv(socket, buffer, sizeof(buffer), 0) < 0) {
      cout << "[Error]: Failed to recieve message" << endl;
      return "";
   }
   return buffer;
}

int login(string username, string password) {
   UNUSED(username);
   UNUSED(password);
   return 0;
}


int guest(string username, string password) {
   UNUSED(username);
   UNUSED(password);
   return 0;
}

