#include "HumanA.hpp"
#include "Weapon.hpp"

HumanA::HumanA(std::string input1, const Weapon& club)
    : Tool(club), name(input1) {}

HumanA::~HumanA()
{

}

void    HumanA::attack() const
{
    std::cout << name << "attacks with their" << Tool.getType() << std::endl;
}