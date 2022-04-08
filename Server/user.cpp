#include "user.hpp"
#include "glob.hpp"

User::User(std::string u, std::string p){
    this->u_name = u;
    this->u_pass = p;
}

User::User(){
    this->u_name = "";
    this->u_pass = "";
}

User::User(std::string T){
    std::stringstream is(T);
    getline(is, this->u_name, ':');
    getline(is, this->u_pass,'/');
    std::string l_str; std::stringstream l_buf;
    getline(is, l_str,'/'); l_buf << l_str;
    std::string m_str; std::stringstream m_buf;
    getline(is, m_str,'\n'); m_buf << m_str;
    std::cout << "MSG: " << m_str << std::endl;
    while(getline(l_buf,l_str,':')){
        this->locations.push_back(Location(l_str));
    }
    std::replace(m_str.begin(),m_str.end(),':',' ');
    std::stringstream ss(m_str);
    int m;
    while(ss >> m){
        this->messages.push_back(m);
    }
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

Location User::get_loc(int l){
    return this->locations[l];
}

bool User::add_loc(Location l){
    this->locations.push_back(l);
    return this->locations[this->locations.size()-1] == l;
}

bool User::add_msg(int m){
    this->messages.push_back(m);
    return true;
}

std::string User::get_msgs(){
    std::string o = "";
    int iter = 0;
    for(auto &it: this->messages){
        if(iter >= 10)
            break;
        o += msgs[it].content + ":";
        iter++;
    }
    if(this->messages.size() == 0)
        o = "None";
    return o;
}


bool User::rem_loc(int l){
    int n = this->locations.size();
    this->locations.erase(this->locations.begin() + l);
    return n > (int)this->locations.size();
}

std::string User::get_name(){
    return this->u_name;
}

std::string User::get_sub_locs(){
    std::string o;
    for(auto &it: this->locations)
        o += it.getName() + ":";
    if((int)this->locations.size() == 0)
        o = "None";
    return o;
}

bool User::has_loc(Location l){
    for(auto &it: locations){
        if(l == it)
            return true;
    }
    return false;
}