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
        User(std::string u, std::string p, std::vector<Location> l, std::vector<int> m);
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

        friend std::istream& operator>>(std::istream& is, User& u){
            getline(is, u.u_name, ':');
            getline(is, u.u_pass,'/');
            std::string l_str; std::stringstream l_buf;
            getline(is, l_str,'/'); l_buf << l_str;
            std::string m_str; std::stringstream m_buf;
            getline(is, m_str, '\n'); m_buf << m_str;

            while(getline(l_buf,l_str,':')){
                u.locations.push_back(Location(l_str));
            }
            std::stringstream ss;
            while(getline(m_buf,m_str,':')){
                ss << l_str; int l;
                ss >> l;
                u.messages.push_back(l);
            }

            return is;
        }
};


#endif