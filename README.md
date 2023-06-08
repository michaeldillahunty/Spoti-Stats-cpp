## Extra Libraries:
- cpprestsdk (https://github.com/microsoft/cpprestsdk)
- libcurl (https://curl.se/libcurl/)
- nlohmann/json (https://github.com/nlohmann/json)
(On mac, brew install to install)

## Compile Instructions:
1) Clone the repository
2) `cd` into the repo
3) `mkdir build` if a build directory doesn't already exist
4) `cd build`
5) Run `cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl -DOPENSSL_LIBRARIES=/usr/local/Cellar/openssl/1.0.2s/lib ..` to get all necessary dependencies
6) Run `make` to compile
7) To run without the server (guest mode) use `./spotify`
   - If you wish to run with the server (user mode): 
      a. First run `./server`
      b. Open another terminal instance and navigate to the `build` dir 
         - With the other instance still running the server, in the new instance run `./spotify`
