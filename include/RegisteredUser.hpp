#ifndef REGISTERED_USER_HPP
#define REGISTERED_USER_HPP
#include "SpotifyAPI.hpp"

class RegisteredUser {
   private:
      std::string username;
      std::string password;

   public: 
      void SetLogin(std::string username, std::string password){
         this->username = username; 
         this->password = password; 
      }
      std::string GetLoginUsername(){
         return username; 
      }
      std::string GetLoginPassword(){
         return password; 
      }

      
};

#endif