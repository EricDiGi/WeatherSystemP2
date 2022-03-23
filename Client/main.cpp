#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#define PORT 60049
#define DATA_LEN 1280

using namespace std;

struct sockaddr_in localSock;
struct ip_mreq group;

int client_fd;
char buffer[DATA_LEN];

int main(int argc, char** argv){
    if((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Could not make socket !!!");
        exit(EXIT_FAILURE);
    } else printf("Socket made...\n");

    std::string ip;
    cout << "Enter hostname: ";
    cin >> ip;
    if(ip == "localhost")
        ip = "127.0.0.1";

    memset((char*)&localSock, 0, sizeof(localSock));
    localSock.sin_family = AF_INET;
    localSock.sin_port = htons(PORT);
    localSock.sin_addr.s_addr = inet_addr((char*)ip.c_str());

    if(connect(client_fd, (struct sockaddr*)&localSock, sizeof(localSock)) < 0){
        perror("Failed to bind !!!");
        close(client_fd);
        exit(EXIT_FAILURE);
    } else printf("Socket ... OK ...\n");

}