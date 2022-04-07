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
    getline(ss,ret,':');
    if(ret == "is_reg"){
        ss >> pos;
        std::cout << "this is loc:" << pos << "\n";
        while(dash()){};
    }
    else
        return;
}

void logout(){
    std::stringstream ss;
    ss << "I#" << pos;
    std::cout << ss.str() << "\n";
    send(ss.str());
    std::string ret = read();
    std::cout << ret << "\n\n";
}

std::string build_msg(std::string from, std::string to){
    std::string msg;
    std::cout << "Message:";
    getline(std::cin,msg,'\n');
    return "(from, " + from + ")(to, "+ to + ")(>> " + msg + " <<)";
}


bool dash(){
    while(1){
        std::stringstream ss;
        std::string ret;
        int iter;

        std::cout << "\nPlease Select an Option:\na. Subscribe to a location\nb. Unsubscribe from a location\nc. See the online users\nd. Send a message to a user\ne. Send a group message to a location\nf. See all the locations that the client has subscribed to\ng. See the last 10 messages received\nh. Change password\ni. Logout\n";

        char in = 0;

        std::cout << "Enter Character: ";
        std::cin >> in;
        std::string s(1,in);
        // send(s+"#");
        // std::cout << read() << std::endl;

        switch(in){
            case 'a':
                ss << "l#";
                send(ss.str());
                std::cout << "\nALL LOCATIONS:\n";
                ss.str(read());
                while(getline(ss,ret, ':')){
                    std::cout << ret << "\n";
                }
                std::cout << "Enter Number:"; 
                std::cin >> ret;
                ret = "A#" + std::to_string(pos) +":"+ ret;
                send(ret);
                std::cout << read() << std::endl;
                return true;
            case 'b':
                ss << "F#" << pos;
                send(ss.str());
                std::cout << "You are subscribed to:\n";
                ss.str("");
                ss << read();
                iter = 1;
                while(getline(ss,ret, ':')){
                    std::cout << iter << ". " << ret << "\n";
                    iter++;
                }
                std::cout << "Enter a number: "; std::cin >> ret;
                ret = "B#" + std::to_string(pos) + ":" + ret;
                send(ret);
                std::cout << read() << std::endl;
                return true;
            case 'c':
                ss << "C#";
                send(ss.str());
                ss.str("");
                ss << read();
                std::cout << "\nALL USERS:\n";
                while(getline(ss,ret, ':')){
                    std::cout << ret << "\n";
                }
                std::cout << std::endl;
                return true;
            case 'd':
                std::cout << "Enter Recipient Username:";
                std::cin >> ret;
                ret = "D#" + std::to_string(pos) + ":" + ret + ":" + build_msg(std::to_string(pos),ret);
                send(ret);
                std::cout << read() << std::endl;
                return true;
            case 'e':
                ss << "F#" << pos;
                send(ss.str());
                std::cout << "You are subscribed to:\n";
                ss.str("");
                ss << read();
                iter = 1;
                while(getline(ss,ret, ':')){
                    std::cout << iter << ". " << ret << "\n";
                    iter++;
                }
                std::cout << "Enter a number: "; std::cin >> ret;
                ret = "E#" + std::to_string(pos) + ":" + ret + ":" + build_msg(std::to_string(pos),ret);
                send(ret);
                std::cout << read() << std::endl;
                return true;
            case 'f':
                ss << "F#" << pos;
                send(ss.str());
                std::cout << "You are subscribed to:\n";
                ss.str("");
                ss << read();
                while(getline(ss,ret, ':')){
                    std::cout << ret << "\n";
                }
                return true;
            case 'g':
                send("G#"+std::to_string(pos));
                ss << read();
                while(getline(ss,ret, ':')){
                    std::cout << ret << "\n";
                }
                return true;
            case 'h':
                ss << "H#" << pos << ":";
                std::cout << "Enter Old Password:"; std::cin >> ret; ss << ret << ":";
                std::cout << "Enter New Password:"; std::cin >> ret; ss << ret;
                send(ss.str());
                std::cout << read() << "\n";
                return true;
            case 'i':
                logout();
                return false;
        }
    }
}