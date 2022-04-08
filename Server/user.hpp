#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "location.hpp"
#include "message.hpp"

class User{

    private:
        std::string u_name;
        std::string u_pass;
        std::vector<Location> locations;
        std::vector<int> messages;
    public:
        bool online = false;

        User();
        User(std::string u, std::string p);
        User(std::string T);
        bool is_reg();
        bool is_user(std::string u);
        bool is_auth(std::string u, std::string p);
        bool new_pass(std::string p);
        
        bool add_loc(Location l);
        bool rem_loc(int l);
        bool has_loc(Location l);
        
        bool add_msg(int m);
        std::string get_msgs();

        std::string get_sub_locs();

        std::string get_name();
        Location get_loc(int l);

        friend std::ostream& operator<<(std::ostream& os, const User& u){
            os << u.u_name << ":" << u.u_pass << "/";
            int i = 0;
            for(auto &it: u.locations){
                os << it;
                if(i < (int)u.locations.size()-1)
                    os << ":";
                i++;
            }
            os << "/";
            i = 0;
            for(auto &it: u.messages){
                os << it;
                if(i < (int)u.messages.size()-1)
                    os << ":";
                i++;
            }
            return os;
        } 

        // friend std::istream& operator>>(std::istream& is, User& u){
            
        // }
};


#endif