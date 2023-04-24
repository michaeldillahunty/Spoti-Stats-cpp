cmake_minimum_required(VERSION 3.0)

project(V1)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Werror")
set(CMAKE_BUILD_TYPE debug)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(server_lib SHARED src/server_commands.cpp src/server_commands.cpp src/Users.cpp)
add_library(client_lib SHARED src/client_commands.cpp src/client_commands.cpp)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

# TESTS
# add_executable(server_test test/server_test.c include/server.h lib/server.c)

target_link_libraries(client client_lib)
target_link_libraries(server server_lib)
# target_link_libraries(server_test server_lib)

find_package(nlohmann_json 3.2.0 REQUIRED)
find_pack()