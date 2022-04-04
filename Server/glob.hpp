#ifndef GLOB_HPP
#define GLOB_HPP

#include <vector>
#include <mutex>
#include "location.hpp"
#include "user.hpp"

extern std::mutex lock;
extern std::vector<Location> locats;
extern std::vector<User> accs;
extern std::vector<User*> active_users;

#endif