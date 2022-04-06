#include <sstream>
#include <iostream>
#include <iterator>
#include "action_handler.hpp"
#include "glob.hpp"

// incoming packets of form:
// cmd_code#func_op1:func_op2
Handler::Handler(std::string buffer){
    this->out = "";
    std::stringstream dbuf(buffer);
    std::cout << buffer << "\n";
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
    else if(this->cmd == "H")
        change_password(func_ops[0],func_ops[1],func_ops[2]);
    else if(this->cmd == "I")
        logout(func_ops[0]);
    else
        this->out = "This is text :)";
}

void Handler::login_auth(std::string u, std::string p){

    std::stringstream ss;
    int iter = 0;
    lock.lock();
        for(auto &it: accs){
            if(it.is_auth(u,p)){
                it.online = true;
                ss << "is_auth:" << iter;
                this->out = ss.str();
                lock.unlock();
                return;
            }
            iter++;
        }
    lock.unlock();
    this->out = "not_auth:";

}

void Handler::register_user(std::string u, std::string p){
    std::stringstream ss;
    User u_ = User(u,p);
    if(u_.is_reg()){
        u_.online = true;
        lock.lock();
            accs.push_back(u_);
            ss << "is_reg:" << accs.size()-1;
        lock.unlock();
        this->out = "";
        this->out = ss.str();
        return;
    }
    this->out = "not_reg";
    return;
}

void Handler::logout(std::string pos){
    std::stringstream p(pos);
    int P;
    p >> P;
    lock.lock();
        accs[P].online = false;
    lock.unlock();
    this->out = "User Logout";
}

void Handler::all_online(){
    std::stringstream ss;
    std::cout << ">>> accessing active list\n";
    lock.lock();
        for(auto &it: accs){
            if(it.online)
                ss << it.get_name() << ":";
        }
        // for(auto &it: accs){
        //     if(it.online)
        //         std::cout << it.get_name() << "\n";
        // }
    lock.unlock();
    this->out = ss.str();
}

void Handler::change_password(std::string loc_, std::string old, std::string new_){
    std::stringstream ss(loc_);
    int loc;
    ss >> loc;
    lock.lock();
        if(accs[loc].is_auth(accs[loc].get_name(),old)){
            if(accs[loc].new_pass(new_))
                this->out = "success";
            else
                this->out = "could not change password";
        }
    lock.unlock();
}

std::string Handler::act(){
    return this->out;
}