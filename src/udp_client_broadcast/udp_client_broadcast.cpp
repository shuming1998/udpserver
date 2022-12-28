#include "udp_client.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>

int main(int argc, char *argv[]) {
  unsigned short port = 5555;
  if (argc > 1) {
    port = atoi(argv[1]);
  }

  std::string ip = "127.0.0.1";
  if (argc > 2) {
    ip = std::string(argv[2]);
  }

  int sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock <= 0) {
    std::cout << "creat socket failed!\n";
    return -1;
  }

  int opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));

  sockaddr_in addr;
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = INADDR_BROADCAST;

  std::string msg = "12345";
  int len = sendto(sock, msg.c_str(), msg.size(), 0, (sockaddr *)&addr, sizeof(addr));
  std::cout << "send size: " << len << '\n';

  char buf[1024] = {0};
  recvfrom(sock, buf, sizeof(buf) - 1, 0, 0, 0);
  std::cout << buf << '\n';

  return 0;
}