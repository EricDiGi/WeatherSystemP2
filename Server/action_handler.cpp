#include <sstream>
#include <iostream>

#include "action_handler.hpp"
#include "glob.hpp"

// incoming packets of form:
// cmd_code#func_op1:func_op2
Handler::Handler(std::string buffer){
    this->out = "";
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

    // Server functions
    if(this->cmd == "L")
        login_auth(func_ops[0],func_ops[1]);
    else if(this->cmd == "R")
        register_user(func_ops[0], func_ops[1]);
    else if(this->cmd == "C")
        all_online();
    else
        this->out = "This is text :)";
}

void Handler::login_auth(std::string u, std::string p){

    std::stringstream ss;
    for(auto &it: accs){
        if(it.is_auth(u,p)){
            active_users.push_back(&it);
            ss << "is_auth:" << active_users.size();
            this->out = ss.str();
            return;
        }
    }
    this->out = "not_auth:";

}

void Handler::register_user(std::string u, std::string p){
    std::stringstream ss;
    User u_ = User(u,p);
    if(u_.is_reg()){
        accs.push_back(u_);
        active_users.push_back(&accs[accs.size()-1]);
        ss << "is_reg:" << active_users.size()-1;
        this->out = "";
        this->out = ss.str();
        return;
    }
    this->out = "not_reg";
    return;
}

void Handler::logout(int pos){
    active_users.erase(active_users.begin()+pos);
}

void Handler::all_online(){
    std::stringstream ss;
    for(auto &it: active_users){
        ss << it->get_name() << ":";
    }
    this->out = ss.str();
}

std::string Handler::act(){
    return this->out;
}