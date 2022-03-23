#ifndef CONN_HPP
#define CONN_HPP

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>

#define PORT 60049
#define DATA_LEN 1280


extern struct sockaddr_in localSock;
extern struct ip_mreq group;

extern int client_fd;
extern char buffer[DATA_LEN];
std::string read();
bool send(std::string content);

#endif