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
    public:
        Handler(std::string buffer);
        // ~Handler();
        std::string act();
};

#endif