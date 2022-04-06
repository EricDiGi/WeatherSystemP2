#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include "location.hpp"

class User{

    private:
        std::string u_name;
        std::string u_pass;
        std::vector<Location> locations;
    public:
        bool online = false;

        User();
        User(std::string u, std::string p);
        
        bool is_reg();
        bool is_user(std::string u);
        bool is_auth(std::string u, std::string p);
        bool new_pass(std::string p);
        
        std::string get_name();

        friend std::ostream& operator<<(std::ostream& os, const User& u){
            os << ">> " << u.u_name << " :: " << u.u_pass << " <<";
            return os;
        } 

};


#endif