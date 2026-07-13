/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:49:57 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 09:59:03 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main(void)
{
	std::string input = "Charizard";
	ScavTrap Scav("Harry");
	FragTrap Frag("Bert");
	Scav.attack(input);
	Scav.guardGate();
	Frag.highFivesGuys();
}
