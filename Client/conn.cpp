#include "conn.hpp"

char buffer[DATA_LEN];

std::string read(){
    memset(buffer, 0, DATA_LEN);
    if(read(client_fd, buffer, DATA_LEN) < 0){
        perror("Could not read server response !!!");
    }
    std::string o(buffer);
    return o;
}

bool send(std::string content){
    if(sendto(client_fd, content.c_str(), content.size()+1, 0, (sockaddr*)&localSock, sizeof(localSock)) < 0){
        perror("Could not send message");
        return false;
    }
    content = "";
    return true;
}