#include "HumanB.hpp"
#include "Weapon.hpp"

HumanB::HumanB(std::string input1)
{
    name = input1;
}

HumanB::~HumanB()
{
}

void    HumanB::setWeapon(const Weapon& club)
{
    Tool2 = &club;
}

void    HumanB::attack()
{
    std::cout << name << "attacks with their" << Tool2->getType() << std::endl;
}