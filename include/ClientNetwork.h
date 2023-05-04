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


using namespace std;


class ClientNetwork {
   private:
      int client_sock_fd = 0;
      struct sockaddr_in sock_addrs; 

   public: 
      bool connect_socket();
      bool send_msg(string msg);
      int login(string username, string password);
      int guest(string username, string password);
      string receive_response();

};

#endif