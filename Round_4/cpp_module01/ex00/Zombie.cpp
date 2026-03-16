#include "Zombie.hpp"
#include <string>
#include <iostream>

Zombie::Zombie(std::string input)
{ 
    name = input;
}

Zombie::~Zombie()
{
    std::cout << "Destroyed:" << getName() << std::endl;
}

std::string Zombie::getName() {return name;}

void    Zombie::announce( void )
{
    std::cout << name << ":" << "BraiiiiiiinnnzzzZ..." << std::endl;
}

int main()
{
    std::string name = "igor";
    std::string name2 = "stein";
    Zombie *igor = newZombie(name);
    randomChump(name2);
    delete igor;
    return (0);
}