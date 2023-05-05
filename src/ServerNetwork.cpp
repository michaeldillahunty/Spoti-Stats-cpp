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
   inet_aton("127.0.0.1", &sock_addrs.sin_addr);


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
   char buffer[MAX_MSG_SERVER];
   strcpy(buffer, msg.c_str());
   if (send(socket, buffer, sizeof(buffer), 0) < 0) {
      cout << "[Error]: Failed to send message" << endl;
      return false;
   }
   return true; 
}

string ServerNetwork::recieve_msg(int socket) {
   char buffer[MAX_MSG_SERVER];
   if (recv(socket, buffer, sizeof(buffer), 0) < 0) {
      cout << "[Error]: Failed to recieve message" << endl;
      return "";
   }
   return buffer;
}

void ServerNetwork::start_server() {
   ServerNetwork* network = ServerNetwork::getInstance();
   if (network->establish_connection() != true){
      cout << "Failed to connect Server to Socket" << endl;
      return;
   }

   while(1){
      cout << "Server listening for incoming connections..." << endl;
      if ((curr_socket = network->accept_connection()) < 0){
         cout << "Failed to accept connection to Client" << endl;
         continue;
      }

      string msg = network->recieve_msg(curr_socket);
      if (msg.empty()){
         cout << "Failed to recieve message" << endl;
         continue;
      }

      cout << "Recieved Message: " << msg << endl;

      size_t code_start = msg.find("code="); // search redirect message for authorization code
      if (code_start != string::npos){
         string code = msg.substr(code_start + 5, 40);
         string grant_type = ""; // add the authorization code here 
         string client_id = GetClientID();
         string client_secret = GetClientSecret();
         string redirect_uri = GetAuthURI();
         

         string response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
         send_msg(curr_socket, response);
      } else {
         string response = "HTTP/1.1 400 Bad Request\r\nContent-Length: 0\r\n\r\n";
         send_msg(curr_socket, response);
      }
   }
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

