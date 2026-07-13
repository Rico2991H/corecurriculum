/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:04:08 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 11:22:31 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include <string>
#include <iostream>

FragTrap::FragTrap() : ClapTrap()
{
	setAttackDamage(30);	
	setEnergyPoints(100);
	setHitPoints(100);
	std::cout << "FragTrap Def Contructor called for <<" << this->getName() << "\n";
}

FragTrap::FragTrap(std::string input) : 
ClapTrap(input) 
{
	setAttackDamage(30);
	setEnergyPoints(100);
	setHitPoints(100);
	std::cout << "FragTrap Constructor called for " << this->getName() << "\n";
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap Destructor called\n";
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "Hey! High Five!" << std::endl;	
}