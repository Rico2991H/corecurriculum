#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"

class HumanB
{
public:
    HumanB(std::string input1);
    ~HumanB();
    void    setWeapon(const Weapon& tool);
    void    attack();

private:
    const Weapon* Tool2;
    std::string name;
};

#endif
