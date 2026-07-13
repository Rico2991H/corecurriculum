/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:49:57 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 12:28:41 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "ClapTrap.hpp"

void	test1(ClapTrap Harry)
{
	std::cout << "Running test 1 with a single attack, repair, damage action \n";
	Harry.attack("Alfred");
	Harry.beRepaired(10);
	Harry.takeDamage(20);
}
void	test2(ClapTrap Harry)
{
	std::cout << "Running test 2 with multiple attack,repair, damage actions\n";
	for (int i = 0; i < 8; i++)
	{
		Harry.attack("Alfred");
		Harry.beRepaired(10);
		Harry.takeDamage(20);
	}
}
int	main(void)
{
	ClapTrap ClapTrap("Harry");
	test1(ClapTrap);
	test2(ClapTrap);
}


