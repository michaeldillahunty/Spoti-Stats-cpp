cmake_minimum_required(VERSION 3.0)

project(spoti-stats)

set(CMAKE_COLOR_MAKEFILE ON)
# set(CMAKE_C_FLAGS "-std=c17 -Wall -Wextra -Wshadow -Werror")
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -ggdb -O0 ${CURL_CXXFLAGS}")
set(CMAKE_BUILD_TYPE debug)


# find_package(nlohmann_json 3.2.0 REQUIRED)
# find_package(nlohmann_json REQUIRED
#     CONFIG
#     PATHS "/usr/lib/cmake/"
# )

find_package(nlohmann_json REQUIRED)
include_directories(${nlohmann_json_INCLUDE_DIRS})

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
set(LIBS ${LIBS} ${CURL_LIBRARIES} ${nlohmann_json_INCLUDE_DIRS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# include_directories("${PROJECT_SOURCE_DIR}/src/utils/nlohmann/json.hpp")

add_executable(server src/ServerNetwork.cpp src/server_main.cpp)
add_executable(spotify src/ClientNetwork.cpp src/SpotifyAPI.cpp src/main.cpp)

target_link_libraries(server nlohmann_json::nlohmann_json ${CURL_LIBRARIES})
target_link_libraries(spotify nlohmann_json::nlohmann_json ${CURL_LIBRARIES})



# target_link_libraries(client PRIVATE nlohmann_json::nlohmann_json)
# target_link_libraries(client client_lib spotify_lib)
# target_link_libraries(server server_lib)
# target_link_libraries(server_test server_lib)
