/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:07:47 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/31 17:32:16 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Character.hpp"
#include <string>
#include <iostream>

Character::Character()
{
	std::cout << "Def Character Constructor called\n";
}

Character::Character(std::string input) : ICharacter(input)
{
	std::cout << "Character constructor called\n";
}
Character::Character(const Character& other) : ICharacter(other)
{
	std::cout << "Copy constructor called\n";
}

Character& Character::operator=(const Character& other)
{
	std::cout << "Copy assignment operator called\n";
	if(this != &other)
	{
		ICharacter::operator=(other);
	}
	return (*this);
}

Character::~Character()
{
    std::cout << "Destructor called\n";
}

std::string const&	Character::getName() const
{
	return(name);
}
void				Character::equip(AMateria* m)
{
	for ( int i = 0 ; i < 4 ; i++)
	{
		if (i == InvAmount)
		{
			inventory[i] = m;
			std::cout << m->getType() << " Added to inventory \n";
			return;
		}
	}
	std::cout << "Inventory is full \n";
}
void 				Character::unequip(int idx)
{
	for (int i = 0; i < 4 ; i++)
	{
		if (i == idx)
		{
			delete inventory[i];
			inventory[i] = NULL;
			std::cout << "Item removed from inventory \n";
		}
	}
	std::cout << "Could not find item in inventory \n";
}
void				Character::use(int idx, ICharacter& target )
{
	for (int i = 0; i < 4; i++)
	{
		if (i == idx)
		{
			std::cout << name << " uses" << inventory[i]->getType();
			if (inventory[i]->getType() == "ice")
				std::cout << "*shoots an ice bolt at" << target.getName() << std::endl;
			if (inventory[i]->getType() == "cure")
				std::cout <<  "* heals" << target.getName() << "’s wounds *" << std::endl;
		}
	}	
} 
