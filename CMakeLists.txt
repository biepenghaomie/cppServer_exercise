cmake_minimum_required(VERSION 3.1)

project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(header)
aux_source_directory(src srcCode)

add_executable(client client.cpp ${srcCode})
add_executable(server server.cpp ${srcCode})
