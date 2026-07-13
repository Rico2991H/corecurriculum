/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:24:28 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/19 11:24:34 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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