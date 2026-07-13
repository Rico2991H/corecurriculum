/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:00:36 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 13:00:37 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include <iostream>
#include <string>
class FragTrap : public ClapTrap
{
	public:
		FragTrap();
		FragTrap(std::string input);
		~FragTrap();
		void highFivesGuys(void);
	private:
};

#endif
