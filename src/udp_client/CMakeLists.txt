aux_source_directory(. SRC)
add_executable(udp_client ${SRC})
target_link_libraries(udp_client pthread)