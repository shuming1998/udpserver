aux_source_directory(. SRC)
add_executable(udp_server ${SRC})
target_link_libraries(udp_server pthread)