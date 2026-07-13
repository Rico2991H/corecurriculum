/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:26:01 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 10:30:12 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"
#include "Weapon.hpp"

HumanB::HumanB(std::string input1) 
    : name(input1), Tool2(NULL)
{
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
    if(Tool2)
        std::cout << name << "attacks with their" << Tool2->getType() << std::endl;
    else
        std::cout <<name << "has no weapon" << std::endl;
}