/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:59:20 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/28 12:32:23 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP
#include <string>
#include <iostream>
#include <climits>

class ClapTrap
{
	public:
		ClapTrap();
		ClapTrap(std::string input);
		ClapTrap(const ClapTrap& other);
		ClapTrap& operator=(const ClapTrap& other);

		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);

		void setEnergyPoints(int nb);
		void setHitPoints(int nb);
		void setAttackDamage(int nb);

		unsigned int			getAttackDamage();
		unsigned int			getEnergyPoints();
		unsigned int			getHitPoints();
		std::string	getName();

		virtual ~ClapTrap();

	protected:
		std::string 			Name;
		unsigned int			hitPoints;
		unsigned int			energyPoints;
		unsigned int			attackDamage;
};

#endif
