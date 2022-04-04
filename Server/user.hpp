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
        User(std::string u, std::string p);
        bool is_reg();
        bool is_user(std::string u);
        bool is_auth(std::string u, std::string p);
        
        std::string get_name();

};

#endif