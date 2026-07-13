/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:58:58 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/28 12:29:38 by rhoogend         ###   ########.fr       */
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
		ClapTrap(std::string input);
		ClapTrap(const ClapTrap& other);
		ClapTrap& 	operator=(const ClapTrap& other);
		void 		attack(const std::string& target);
		void 		takeDamage(unsigned int amount);
		void 		beRepaired(unsigned int amount);
		
		~ClapTrap();

	private:
		std::string 			Name;
		unsigned int			hitPoints;
		unsigned int			energyPoints;
		unsigned int			attackDamage;

};

#endif
