#ifndef SERVER_NETWORK_H 
#define SERVER_NETWORK_H

// #include "SpotifyAPI.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <string>
#include <vector>
#include <algorithm>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <arpa/inet.h>

using namespace std;
using json = nlohmann::json;

// #include "User.h"
// #include "Singleton.h"

#define SERVER_PORT 8080
#define MAX_PENDING 3
#define MAX_MSG 4096

class ServerNetwork {
   private:
      int server_sock_fd, curr_socket;
      struct sockaddr_in sock_addrs; 
      string client_id = "23ba501c09bd4194b3f2771c98fb5814";
      string client_secret = "eb80eac6f244443fae50300fc8db1479";
      string auth_uri = "https://accounts.spotify.com/en/authorize?client_id=23ba501c09bd4194b3f2771c98fb5814&response_type=code&redirect_uri=http%3A%2F%2Flocalhost%3A8888%2Fcallback&show_dialog=true&scope=user-read-private%20user-read-email%20user-modify-playback-state%20user-read-playback-position%20user-library-read%20streaming%20user-read-playback-state%20user-read-recently-played%20playlist-read-private";
      string access_token_uri = "http://localhost:8888/callback";

   public: 
      ServerNetwork(){}
      bool establish_connection();
      int establish_connection(int socket);
      int accept_connection();
      bool send_msg(int socket, string msg);
      int login(string username, string password);
      int guest(string username, string password);
      string recieve_msg(int socket);
      
      void start_server();

      string GetClientID() { return this->client_id; }
      string GetClientSecret() { return this->client_secret; }
      string GetAuthURI() { return this->auth_uri; }
      string GetTokenURI() { return this->access_token_uri; }

      // ServerNetwork(string client_id) : client_id(client_id){}
};

#endif