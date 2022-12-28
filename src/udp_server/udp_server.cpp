#include "udp_server.hpp"

UdpServer::UdpServer() : sock_(0), addr_(nullptr) {}

UdpServer::~UdpServer() {}

int UdpServer::creatSock() {
  sock_ = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock_ <= 0) {
    std::cout << "creat socket failed!\n";
    return -1;
  }
  return sock_;
}

void UdpServer::closeSock() {
  if (sock_ <= 0) {
    return;
  }

  close(sock_);

  if (addr_) {
    delete addr_;
  }
  addr_ = nullptr;
  sock_ = 0;
}

bool UdpServer::bind(unsigned short port) {
  if (sock_ <= 0) {
    creatSock();
  }
  sockaddr_in addr;
  bzero(&addr, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (0 != ::bind(sock_, (sockaddr *)&addr, sizeof(addr))) {
    std::cout << "bind port " << port << " failed!\n";
    return false;
  }

  std::cout << "bind port " << port << " success!\n";
  listen(sock_, 20);
  return true;
}

int UdpServer::recv(char *buf, int bufSize) {
  if (sock_ <= 0) {
    return 0;
  }

  if (!addr_) {
    addr_ = new sockaddr_in();
  }

  socklen_t addrSize = sizeof(sockaddr_in);
  bzero(addr_, addrSize);
  int len = recvfrom(sock_, buf, bufSize, 0, (sockaddr *)addr_, &addrSize);

  return len;
}

// int main(int argc, char *argv[]) {
//   unsigned short port = 8765;
//   if (argc > 1) {
//     port = atoi(argv[1]);
//   }

//   int sock = socket(AF_INET, SOCK_DGRAM, 0);
//   if (sock <= 0) {
//     std::cout << "creat socket failed!\n";
//     return -1;
//   }

//   sockaddr_in addr;
//   bzero(&addr, sizeof(addr));
//   addr.sin_family = AF_INET;
//   addr.sin_port = htons(port);
//   addr.sin_addr.s_addr = htonl(INADDR_ANY);

//   if (0 != ::bind(sock, (sockaddr *)&addr, sizeof(addr))) {
//     std::cout << "bind port " << port << " failed!\n";
//     return -2;
//   }

//   std::cout << "bind port " << port << " success!\n";
//   listen(sock, 20);

//   sockaddr_in clientAddr;
//   socklen_t len = sizeof(clientAddr);
//   char buf[10240] = {0};
//   int dataSize = recvfrom(sock, buf, sizeof(buf), 0, (sockaddr *)&clientAddr, &len);
//   if (dataSize <= 0) {
//     std::cout << "recvfrom failed!\n";
//     return -3;
//   }

//   std::cout << inet_ntoa(clientAddr.sin_addr) << ':' << ntohs(clientAddr.sin_port) << '\n';
//   buf[dataSize] = '\0';
//   std::cout << "clientAddr: " << std::string(buf) << '\n';

//   std::string response = "67890";
//   sendto(sock, response.c_str(), response.size(), 0, (sockaddr *)&clientAddr, sizeof(clientAddr));


//   return 0;
// }