#include "location.hpp"
#include "glob.hpp"

Location::Location(std::string name){
    this->name = name;
}

std::string Location::getName(){
    return this->name;
}