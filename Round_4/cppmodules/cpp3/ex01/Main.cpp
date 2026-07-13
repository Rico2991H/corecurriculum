/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:49:57 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 10:56:29 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

void	test1(ScavTrap robot)
{
	std::cout << "Running test with " << robot.getName() << std::endl; 
	robot.attack("Alfred");
	robot.beRepaired(10);
	robot.takeDamage(20);
}
void	test2(ClapTrap Harry)
{
	std::cout << "Running test 2 with Claptrap " << Harry.getName() << std::endl;
	Harry.attack("Alfred");
	Harry.beRepaired(10);
	Harry.takeDamage(20);
}

int main(void)
{
	std::string input = "Charizard";
	ScavTrap Scav("Harry the ScavTrap");
	ClapTrap Clap("Bob the ClapTrap");
	test1(Scav);
	test2(Clap);
	Scav.attack(input);
	Scav.guardGate();
}
