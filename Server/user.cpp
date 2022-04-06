#include "user.hpp"

User::User(std::string u, std::string p){
    this->u_name = u;
    this->u_pass = p;
}

User::User(){
    this->u_name = "";
    this->u_pass = "";
}

bool User::is_reg(){
    return (this->u_name.size() > 0 && this->u_pass.size() > 0);
}

bool User::is_auth(std::string u, std::string p){
    return (this->u_name == u && this->u_pass == p);
}

bool User::new_pass(std::string p){
    this->u_pass = p;
    return this->u_pass == p;
}

bool User::add_loc(Location l){
    this->locations.push_back(l);
    return this->locations[this->locations.size()-1] == l;
}

std::string User::get_name(){
    return this->u_name;
}

std::string User::get_sub_locs(){
    std::string o;
    for(auto &it: this->locations){
        o += it.getName() + ":";
    }
    return o;
}