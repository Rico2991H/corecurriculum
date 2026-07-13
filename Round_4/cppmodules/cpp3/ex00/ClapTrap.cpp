/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:09:08 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/28 12:29:13 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string input)
	:	Name(input),
		hitPoints(10),
		energyPoints(10),
		attackDamage(3)
{
	std::cout << "Constructor called\n";
}

ClapTrap::ClapTrap(const ClapTrap& other) 
	: 	Name(other.Name), 
		hitPoints(other.hitPoints), 
		energyPoints(other.energyPoints),
		attackDamage(other.attackDamage) 
{
	std::cout << "Copy consturctor called\n";
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << "Copy assignment operator called\n";
	if(this != &other)
	{
		attackDamage = other.attackDamage;
		energyPoints = other.energyPoints;
		hitPoints = other.hitPoints;
		Name = other.Name;
	}
	return (*this);
}

void ClapTrap::attack(const std::string& target)
{
	if (energyPoints > 0 && hitPoints > 0)
	{
		std::cout << "ClapTrap " << Name << " attacks " << target << " causing " << attackDamage << " points of damage!\n";
		energyPoints--;
	}
	else
		std::cout << "ClapTrap has not enough energypoints  or hitpoints to attack.\n";
}
void ClapTrap::takeDamage(unsigned int amount)
{
	
	std::cout << "ClapTrap " << Name << " suffers an attack, causing " << amount << " points of damage!\n";
	if ( amount > hitPoints)
	{
		hitPoints = 0;
	}
	else
		hitPoints -= amount;
	if (hitPoints == 0)
		std::cout << "ClapTrap " << Name << " has taken too much Damage Claptrap is down \n";
}
void ClapTrap::beRepaired(unsigned int amount)
{
	if (energyPoints > 0)
	{
		std::cout << "ClapTrap " << Name << " is being repaired, restoring " << amount << " of hit points!\n";
		energyPoints--;
		if (hitPoints > UINT_MAX - amount)
			hitPoints = UINT_MAX;
		else
			hitPoints += amount;
	}
	else
		std::cout << "Claptrap has not enough energy points to be repaired.\n";
}

ClapTrap::~ClapTrap()
{
    std::cout << "Destructor called\n";
}
