#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>

class Location{
    private:
        std::string name;
        
    public:
        Location(std::string name);
        // ~Location();
        std::string getName();
        bool operator==(Location& a){
            return a.name == this->name;
        }
};

#endif