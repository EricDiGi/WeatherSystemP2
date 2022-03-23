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
//char buffer[DATA_LEN];

std::string read();//{
//     if(read(client_fd, buffer, DATA_LEN) < 0){
//         perror("Could not read server response !!!");
//     }
//     std::string o(buffer);
//     return o;
// }

bool send(std::string content);//{
//     if(sendto(client_fd, content.c_str(), content.size()+1, 0, (sockaddr*)&localSock, sizeof(localSock)) < 0){
//         perror("Could not send message");
//         return false;
//     }
//     return true;
// }

#endif