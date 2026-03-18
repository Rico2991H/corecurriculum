#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"

class HumanA
{
public:
    HumanA(std::string input1, const Weapon& tool);
    ~HumanA();
    void    attack() const;

private:
    const::Weapon& Tool;
    std::string name;
};

#endif
