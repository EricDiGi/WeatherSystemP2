#include "interface.hpp"
#include "conn.hpp"
#include <sstream>
#include <iostream>

int pos = -1;

void accounting(){
    printf("Please chose a Number:\n1. Login\n2. Register\n3. Quit\n\n");
    int op = -1;
    std::cout << "Number: ";
    std::cin >> op;
    switch(op){
        case 1:
            login();
            return;
        case 2:
            register_();
            return;
        case 3:
            exit(EXIT_SUCCESS);
        default:
            return;
    }
}

void login(){
    std::string u_name, u_pass;

    std::cout << "Username: ";
    std::cin >> u_name;
    std::cout << "Password: ";
    std::cin >> u_pass;

    send("L#"+u_name+":"+u_pass);
    std::string ret = read();
    std::cout << "##" << ret << std::endl;
    std::stringstream ss(ret);
    std::string temp;
    getline(ss,temp, ':');
    if(temp == "is_auth"){
        ss >> pos;
        while(dash()){};
    }
    else
        return;
}


void register_(){
    std::string u_name, u_pass;

    std::cout << "Username: ";
    std::cin >> u_name;
    std::cout << "Password: ";
    std::cin >> u_pass;

    send("R#"+u_name+":"+u_pass);
    std::string ret = read();
    std::cout << "##" << ret << std::endl;
    std::stringstream ss(ret);
    if(ret.substr(0,6) == "is_reg"){
        ss >> pos;
        while(dash()){};
    }
    else
        return;
}

void logout(){
    std::stringstream ss("Z#");
    ss << pos;
    send(ss.str());
    std::string ret = read();
    std::cout << ret << "\n\n";
}



bool dash(){
    while(1){
        std::stringstream ss;
        std::string ret;

        std::cout << "Please Select an Option:\na. Subscribe to a location\nb. Unsubscribe from a location\nc. See the online users\nd. Send a message to a user\ne. Send a group message to a location\nf. See all the locations that the client has subscribed to\ng. See the last 10 messages received\nh. Change password\ni. Logout\n";

        char in = 0;

        std::cout << "Enter Character: ";
        std::cin >> in;

        send(s+"#");
        std::cout << read() << std::endl;

        switch(in){
            case 'i':
                logout();
                return false;
            case 'c':
                ss << "C#";
                send(ss.str());
                ss.str("");
                ss << read();
                std::string temp;
                std::cout << "ALL USERS:\n";
                while(getline(ss,temp, ':')){
                    std::cout << temp << "\n";
                }
                std::cout << std::endl;
                return true;
        }
    }
}