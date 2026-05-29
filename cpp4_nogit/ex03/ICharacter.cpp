/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 11:04:19 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/31 11:05:30 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ICharacter.hpp"
#include <string>
#include <iostream>
#include "AMateria.hpp"
#include "Character.hpp"

ICharacter::ICharacter()
{
	std::cout << "Def Constructor called\n";
}

ICharacter::ICharacter(std::string input)
{
	std::cout << "ICharacter constructor called\n";
	name = input;
}

ICharacter::ICharacter(const ICharacter& other)
{
	*this = other;
	std::cout << "Copy constructor called\n";

}

ICharacter& ICharacter::operator=(const ICharacter& other)
{
	std::cout << "Copy assignment operator called\n";
	if(this != &other)
	{
		this->name = other.name;
		for (int i = 0; i < other.InvAmount; i++)
			this->inventory[i] = other.inventory[i];
		this->InvAmount = other.InvAmount;
	}
	return (*this);
}

ICharacter::~ICharacter()
{
    std::cout << "Destructor called\n";
}
