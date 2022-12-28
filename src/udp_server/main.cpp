#include "udp_server.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  unsigned short port = 5555;
  if (argc > 1) {
    port = atoi(argv[1]);
  }

  UdpServer udpServer;
  if (!udpServer.bind(port)) {
    return -1;
  }

  char buf[2048] = {0};
  for (;;) {
    int len = udpServer.recv(buf, sizeof(buf));
    if (len <= 0) {
      continue;
    }
    buf[len] = '\0';
    std::cout << buf << '\n';
  }
  return 0;
}