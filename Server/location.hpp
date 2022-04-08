#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>
#include <vector>
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
        bool operator==(std::string& a){
            return a == this->name;
        }

        friend std::ostream& operator<<(std::ostream& os, const Location& l){
            os << l.name;
            return os;
        } 
};

#endif