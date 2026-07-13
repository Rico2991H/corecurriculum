/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:59:57 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 10:36:19 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string input) 
	:	ClapTrap(input) 
{
	setAttackDamage(20);
	setEnergyPoints(50);
	setHitPoints(100);
	std::cout << "ScavTrap Constructor called\n";
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap Destructor called\n";
}

void ScavTrap::attack(const std::string& target)
{
	if (getEnergyPoints() > 0 && getHitPoints() > 0)
	{
		std::cout << "ScavTrap " << getName() << " attacks " << target << " causing " << getAttackDamage() << " points of damage!\n";
		setEnergyPoints(getEnergyPoints() - 1);
	}
	else
		std::cout << "ClapTrap has not enough energy points or hit points to attack.\n";
}

void ScavTrap::guardGate()
{
	std::cout << getName() << " is now in Gate keeper mode.\n";
}