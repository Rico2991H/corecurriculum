#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
#include <string>

class Weapon
{
    public:
        Weapon(std::string input);
        ~Weapon();
        const std::string&  getType() const;
        void                setType(std::string input);

    private:
        std::string type;
};

#endif
