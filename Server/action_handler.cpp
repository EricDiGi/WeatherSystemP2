#include <sstream>
#include <iostream>

#include "action_handler.hpp"
#include "glob.hpp"

// incoming packets of form:
// cmd_code#func_op1:func_op2
Handler::Handler(std::string buffer){
    std::stringstream dbuf(buffer);
    getline(dbuf,this->cmd,'#');
    
    std::string tmp;
    while(getline(dbuf,tmp, ':')){
        func_ops.push_back(tmp);
    }
    std::cout << this->cmd << "\t";
    for(auto &it: this->func_ops){
        std::cout << it << "\t";
    }
    std::cout << std::endl;

    if(this->cmd == "L")
        login_auth(func_ops[0],func_ops[1]);
    else if(this->cmd == "R")
        register_user(func_ops[0], func_ops[1]);
    else
        this->out = "This is text :)";
}

void Handler::login_auth(std::string u, std::string p){
    // for(auto &it: accs){
    //     if(it.u_name == u && it.u_pass == p)
            this->out = "is_auth";
    // }
    // this->out = "not_auth";
}

std::string Handler::act(){
    return this->out;
}