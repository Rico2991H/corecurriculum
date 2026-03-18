#include "Weapon.hpp"

Weapon::Weapon(std::string str1)
{
    setType(str1);
}

Weapon::~Weapon()
{
}

const std::string& Weapon::getType() const {return (type);}

void        Weapon::setType(std::string input)
{
    type = input;
}