#include "Zombie.hpp"
#include <iostream>
#include <string>

Zombie *newZombie( std::string name )
{
    Zombie *New = new Zombie(name);
    New->announce();
    return (New);
}


