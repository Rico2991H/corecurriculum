#include "Zombie.hpp"
#include <iostream>
#include <string>

void randomChump( std::string name )
{
    Zombie New(name);
    New.announce();
}
