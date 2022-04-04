#include "user.hpp"

User::User(std::string u, std::string p){
    this->u_name = u;
    this->u_pass = p;
}

bool User::is_reg(){
    return (this->u_name.size() > 0 && this->u_pass.size() > 0);
}

bool User::is_auth(std::string u, std::string p){
    return (this->u_name == u && this->u_pass == p);
}

std::string User::get_name(){
    return this->u_name;
}