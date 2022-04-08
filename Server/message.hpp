#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <iostream>
#include <string> 

class Message{
    public:
        std::string content;
        int id;
        friend std::ostream& operator<<(std::ostream& os, const Message& m){
            os << m.id << (char)30 << m.content;
            return os;
        } 
};


#endif