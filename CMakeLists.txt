cmake_minimum_required(VERSION 3.15)
project(udpServer)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/src/udp_server)
include_directories(${PROJECT_SOURCE_DIR}/src/udp_client)

add_subdirectory(src/udp_server)
add_subdirectory(src/udp_client)

