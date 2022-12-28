#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

class UdpServer {
public:
  UdpServer();
  ~UdpServer();
  int creatSock();
  void closeSock();
  bool bind(unsigned short port);
  int recv(char *buf, int bufSize);


protected:
  int sock_;

private:
  sockaddr_in *addr_;

};


#endif