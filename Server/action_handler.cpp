#include <sstream>

#include "action_handler.hpp"
#include "glob.hpp"

// incoming packets of form:
// cmd_code#func_op1:func_op2
Handler::Handler(std::string buffer){
    std::stringstream dbuf(buffer);
    getline(dbuf,this->cmd,'#');
    
    std::string tmp;
    while(getline(dbuf,tmp, ':')){
        func_ops.push_back(tmp);
    }
}

std::string Handler::act(){
    return "This is a packet";
}