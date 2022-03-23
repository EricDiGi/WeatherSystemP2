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

};

#endif