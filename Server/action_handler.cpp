#include <sstream>
#include <iostream>
#include <iterator>
#include "action_handler.hpp"
#include "glob.hpp"
#include "message.hpp"

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
    else if(this->cmd =="A")
        subscribe_loc(func_ops[0], func_ops[1]);
    else if(this->cmd =="B")
        unsubscribe_loc(func_ops[0], func_ops[1]);
    else if(this->cmd == "C")
        all_online();
    else if(this->cmd == "D")
        add_msg_usr(func_ops[0],func_ops[1],func_ops[2]);
    else if(this->cmd == "E")
        add_msg_loc(func_ops[0],func_ops[1],func_ops[2]);
    else if(this->cmd == "F")
        see_all_sub_locs(func_ops[0]);
    else if(this->cmd == "l")
        all_locs();
    else if(this->cmd == "G")
        ret_ten_msg(func_ops[0]);
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
    lock.lock();
        for(auto &it: accs){
            if(it.online)
                ss << it.get_name() << ":";
        }
    lock.unlock();
    this->out = ss.str();
}

void Handler::all_locs(){
    std::stringstream ss;
    lock.lock();
        int iter = 1;
        for(auto &it: locats){
            ss << iter << ". " << it.getName() << ":";
            iter++;
        }
    lock.unlock();
    this->out = ss.str();
}

void Handler::subscribe_loc(std::string u_loc, std::string l_loc){
    std::stringstream ss; int u, l;
    ss << u_loc << " " << l_loc; ss >> u >> l;
    lock.lock();
        if(accs[u].add_loc(locats[l-1]))
            this->out = "Now Subscribed to " + locats[l-1].getName() + "!\n";
        else
            this->out = "Could not subscribe\n";
    lock.unlock();
}

void Handler::unsubscribe_loc(std::string u_loc, std::string l_loc){
    std::stringstream ss; int u, l;
    ss << u_loc << " " << l_loc; ss >> u >> l;
    lock.lock();
        if(accs[u].rem_loc(l-1))
            this->out = "Successfully unsubscribed\n";
        else
            this->out = "Failed to unsubscribe\n";
    lock.unlock();
}

void Handler::see_all_sub_locs(std::string u_loc){
    std::stringstream ss; int u;
    ss << u_loc; ss >> u;
    lock.lock();
        this->out = accs[u].get_sub_locs();
    lock.unlock();
}

void Handler::change_password(std::string loc_, std::string old, std::string new_){
    std::stringstream ss(loc_);
    int loc;
    ss >> loc;
    lock.lock();
        if(accs[loc].is_auth(accs[loc].get_name(),old)){
            if(accs[loc].new_pass(new_))
                this->out = "success";
        }
        else
            this->out = "could not change password";
    lock.unlock();
}

std::string Handler::act(){
    return this->out;
}

void Handler::add_msg_loc(std::string u_loc, std::string l_loc, std::string content){
    std::stringstream ss; int u,l;
    ss << u_loc << " " << l_loc; ss >> u >> l;
    lock.lock();
        Message m = Message();
        m.id = (int)msgs.size();
        m.content = "(from, " + accs[u].get_name() + ")(to, " + accs[u].get_loc(l-1).getName() +")" + content;
        msgs.push_back(m);
        for(auto &it : accs){
            if(it.has_loc(accs[u].get_loc(l-1))){
                it.add_msg(m.id);
            }
        }
        this->out = "Message Sent";
    lock.unlock();
}

void Handler::add_msg_usr(std::string u_loc, std::string U_loc, std::string content){
    std::stringstream ss; int u,U;
    ss << u_loc; ss >> u;
    lock.lock();
        int i = 0;
        for(auto &it : accs){
            U = (U_loc == it.get_name()) ? i : -1;
            if(U > -1) break;
            i++;
        }
        if(U >= 0){
            Message m = Message();
            m.id = (int)msgs.size();
            m.content = "(from, " + accs[u].get_name() + ")(to, " + accs[U].get_name() +")" + content;
            msgs.push_back(m);
            accs[U].add_msg(m.id);
            this->out = "Message sent";
        }
        else this->out = "Could not find user >> " + U_loc;
    lock.unlock();
}

void Handler::ret_ten_msg(std::string u_loc){
    std::stringstream ss; int u;
    ss << u_loc; ss >> u;
    lock.lock();
        this->out = accs[u].get_msgs();
    lock.unlock();
}