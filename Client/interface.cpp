#include "interface.hpp"
#include "conn.hpp"

void accounting(){
    printf("Please chose a Number:\n1. Login\n2. Register\n3. Quit\n\n");
    int op = -1;
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
    if(ret == "is_auth")
        dash();
    else
        return;
}


void register_(){}

bool dash(){
    while(1){
        std::cout << "Please Select an Option:\na. Subscribe to a location\nb. Unsubscribe from a location\nc. See the online users\nd. Send a message to a user\ne. Send a group message to a location\nf. See all the locations that the client has subscribed to\ng. See the last 10 messages received\nh. Change password\ni. Logout\n";

        char in = 0;
        std::cin >> in;
        std::string s;
        s.push_back(in);
        std::cout << "## " << s << std::endl;
        send(s+"#");
        std::cout << read() << std::endl;

        if(s == "i")
            return false;
    }
}