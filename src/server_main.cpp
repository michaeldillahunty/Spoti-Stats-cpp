#include "../include/ServerNetwork.h"

/*
   SERVER MAIN
*/
void* ConnectionListener(void* arg);
pthread_mutex_t m;
// ServerNetwork Singleton
ServerNetwork* ServerNetwork::instancePtr = nullptr;

int main(){
    
   if (pthread_mutex_init(&m, NULL) != 0){
      cerr << "Failed to Initialize Mutex" << endl;
   }

   vector<pthread_t> threads; 
   pthread_t thread1; 
   int result;
   result = pthread_create(&thread1, NULL, &ConnectionListener, NULL);
   if (result != 0) {
      cout << "Failed to create thread" << endl;
   }
   pthread_exit(NULL);

   return EXIT_SUCCESS;
}

void* ConnectionListener(void* arg){
   
    ServerNetwork* network = ServerNetwork::getInstance();
    
   //  bool is_connected = true;
   vector<pthread_t*> thread_vec;
   int client_sock_fd; 

   // ServerNetwork network = ServerNetwork();
   if (network->establish_connection() != true) {
      cout << "Failed to connect Server to Socket" << endl; 
   } 

   while (1){
      cout << "Client-Server Connection Successfully Established!" << endl;
      cout << "Server Connected on Port #" << SERVER_PORT << endl;
      if ((client_sock_fd = network->accept_connection()) < 0) {
         cout << "Failed to accept connection to Client" << endl;
      }
      string test_msg = "[From Server]: Initial Test Message";
      network->send_msg(client_sock_fd, test_msg);
      
   }

   /* while (true){
      ServerNetwork network = ServerNetwork();
      // if this is the first time the function is being called
      if (is_connected) {
         if (network.establish_connection()) {
            is_connected = false;
         } else {
            cout << "[Error]: Failed to connect to network" << endl;
         }
      }
      int connections = 0; // connection counter
      if (connections == 0){
         new_sock = network.accept_connection();
         connections += 1; 
      }
      cout << "Connected on socket " << new_sock << endl;
   }   */
}
