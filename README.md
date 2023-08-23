# Spoti-Stats
## Description:
Spoti-Stats is a C++ command line application which utilizes the [Spotify Web API](https://developer.spotify.com/documentation/web-api) and allows you to search songs, tracks, albums, etc.</br>
Goals:
- Use CRUD methods to communicate with API 
- Implement solid programming practices through using OOP and design patterns
- Display good understanding of the C++ language

## Libraries and Packages:
- cpprestsdk (https://github.com/microsoft/cpprestsdk) : `cpprestsdk` from Microsoft used for Client/Server connection and oAuth authorization
- libcurl (https://curl.se/libcurl/) : `libcurl` allows the use of CRUD methods to communicate with the Spotify API
- nlohmann/json (https://github.com/nlohmann/json) : `nlohmann json` API allows for easy JSON manipulation in C++

### Installing Libraries:
- `cpprestsdk` and `nlohmann json`
  - On MacOS: `$ brew install nlohmann-json cpprestsdk`
  - On Linux: `$ sudo apt-get install nlohmann-json-dev`

- `libcurl`:
  1) Install `curl`: </br>
     **Homebrew:** `$ brew install curl`   
     &emsp;&emsp;or   
     **Manually:** Download package from: [https://curl.se/download.html](https://curl.se/download.html)
  3) If any compilation errors occur, try setting:
     ```
     $ export LDFLAGS="-L/usr/local/opt/curl/lib"
     $ export CPPFLAGS="-I/usr/local/opt/curl/include"
     ```

## How to Use:
1) Clone the Spoti-Stats repository: `$ git clone https://github.com/michaeldillahunty/Spoti-Stats-cpp.git`
2) `$ cd Spoti-Stats-cpp`
3) `$ mkdir build`
4) `$ cd build`
5) On MacOS:   
      Run `$ cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl -DOPENSSL_LIBRARIES=/usr/local/Cellar/openssl/1.0.2s/lib ..` to get all necessary dependencies
7) `make` : will create 2 executable files: `server` and `spotify`
8) Run the executable file(s)  
   a. To run in *Guest Mode* (no login required) - Use: `$ ./spotify`   
   b. To run in *User Mode* (requires Spotify login and authentication):   
      a. Run `$ ./server`   
      b. Open another terminal instance and navigate to the same `build` directory    
         - In the second instance run `$ ./spotify`
