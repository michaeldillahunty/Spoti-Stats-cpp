# ECE3220-Final-Project
## Extra Libraries:
- cpprestsdk (https://github.com/microsoft/cpprestsdk)
- libcurl (https://curl.se/libcurl/)
- nlohmann/json (https://github.com/nlohmann/json)
(On mac, brew install to install)

## Compile Instructions:
1) Clone this repo
2) mkdir build
3) cd build
4) cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl -DOPENSSL_LIBRARIES=/usr/local/Cellar/openssl/1.0.2s/lib ..
5) make
6) ./spotify
