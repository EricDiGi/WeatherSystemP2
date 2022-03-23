#ifndef GLOB_HPP
#define GLOB_HPP

#include <vector>
#include <mutex>
#include "location.hpp"

extern std::mutex lock;
extern std::vector<Location> locats;

#endif