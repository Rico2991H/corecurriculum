/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 11:44:21 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 11:02:06 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>
#include <string>

Harl::Harl()
{
}

Harl::~Harl()
{
}

void    Harl::debug(void)
{
	std::cout << "DEBUG:" << "I love some Nasi goreng" << std::endl; 	
}

void    Harl::info(void)
{
	std::cout << "INFO:" << "I can't believe there is no Sambal, I need more sambal" << std::endl;	
}

void    Harl::warning(void)
{
	std::cout << "WARINING:" << "I think you should start making sambal, its not nice without the spice" << std::endl;
}

void    Harl::error(void)
{
	std::cout << "ERROR:" << "DEATH BY SAMBAL" << std::endl;	
}

void    Harl::complain(std::string level)
{
	int		i = 0;
	std::string levels[] = { "DEBUG", "INFO", "WARNING", "ERROR"};
	while (i < 4 && level != levels[i])
		i++;
	switch(i)
	{
		case 0:
			debug();
		case 1:
			info();
		case 2:
			warning();
		case 3:
			error();
			break;
		default:
			std::cout << "Probably complaining about insignificant problems\n";
	}			
}