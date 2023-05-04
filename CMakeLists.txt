cmake_minimum_required(VERSION 3.0)

project(spoti-stats)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -ggdb -O0 ${CURL_CXXFLAGS}")
# -I/usr/local/opt/openssl@3/include 
set(CMAKE_BUILD_TYPE debug)


find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)

set(OPENSSL_ROOT_DIR /usr/local/opt/openssl@1.1/)
set(OPENSSL_LIBRARIES /usr/local/opt/openssl@1.1/lib)
set(LIBS ${LIBS} ${CURL_LIBRARIES} ${nlohmann_json_INCLUDE_DIRS})

# include_directories(/usr/local/opt/openssl@3.1/include/openssl)
include_directories(${nlohmann_json_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/models)

add_executable(server src/ServerNetwork.cpp src/server_main.cpp)
add_executable(spotify src/ClientNetwork.cpp src/SpotifyAPI.cpp src/main.cpp)

target_link_libraries(server nlohmann_json::nlohmann_json cpprestsdk::cpprest ${CURL_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(spotify PRIVATE nlohmann_json::nlohmann_json cpprestsdk::cpprest ${CURL_LIBRARIES} OpenSSL::SSL OpenSSL::Crypto )




# target_link_libraries(client PRIVATE nlohmann_json::nlohmann_json)
# target_link_libraries(client client_lib spotify_lib)
# target_link_libraries(server server_lib)
# target_link_libraries(server_test server_lib)
