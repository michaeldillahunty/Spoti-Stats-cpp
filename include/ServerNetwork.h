#ifndef SERVER_NETWORK_H 
#define SERVER_NETWORK_H

#include "SpotifyAPI.hpp"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

// #include "User.h"
// #include "Singleton.h"

#define SERVER_PORT 8888
#define MAX_PENDING 3
#define MAX_MSG 512

class ServerNetwork {
      int server_sock_fd, curr_socket;
      struct sockaddr_in sock_addrs; 
   public: 
      ServerNetwork(){}
      bool establish_connection();
      int establish_connection(int socket);
      int accept_connection();
      bool send_msg(int socket, string msg);
      int login(string username, string password);
      int guest(string username, string password);
      string recieve_msg(int socket);
};

#endif