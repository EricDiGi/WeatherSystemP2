#ifndef ACTION_HANDLER
#define ACTION_HANDLER

#include <string>
#include <vector>

class Handler{
    private:
        std::string cmd;
        std::vector<std::string> func_ops;
    public:
        Handler(std::string buffer);
        // ~Handler();
        std::string act();
};

#endif