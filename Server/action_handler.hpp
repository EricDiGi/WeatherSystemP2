#ifndef ACTION_HANDLER
#define ACTION_HANDLER

#include <string>
#include <vector>

class Handler{
    private:
        std::string cmd;
        std::vector<std::string> func_ops;

        std::string out;

        void login_auth(std::string u, std::string p);
        void register_user(std::string u, std::string p);
        void logout(std::string pos);
        void change_password(std::string loc_, std::string old, std::string new_);
        void subscribe_loc(std::string u_loc, std::string l_loc);
        void unsubscribe_loc(std::string u_loc, std::string l_loc);
        void see_all_sub_locs(std::string u_loc);
        
        void add_msg_loc(std::string u_loc, std::string l_loc, std::string content);
        void add_msg_usr(std::string u_loc, std::string U_loc, std::string content);
        void ret_ten_msg(std::string u_loc);
        
        void all_online();
        void all_locs();

    public:
        Handler(std::string buffer);
        // ~Handler();
        std::string act();
};

#endif