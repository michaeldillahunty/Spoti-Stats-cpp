#ifndef CLIENT_NETWORK_H
#define CLIENT_NETWORK_H

// #include "SpotifyAPI.hpp"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <cstring>
#include <vector>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

// 8888
#define SERVER_PORT 8080
#define MAX_MSG_CLIENT 4096


class ClientNetwork {
   private:
      int client_sock_fd = 0;
      struct sockaddr_in sock_addrs; 

   public: 
      bool connect_socket();
      bool send_msg(std::string msg);
      int login(std::string username, std::string password);
      int guest(std::string username, std::string password);
      std::string receive_response();

};

#endif