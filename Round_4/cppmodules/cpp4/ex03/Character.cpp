/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:07:47 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/01 13:57:33 by rhoogend         ###   ########.fr       */
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
	for (int i = 0 ; i < 4 ; i++)
	{
		if(inventory[i])
			delete inventory[i];
	}
    std::cout << "Destructor called\n";
}

std::string const&	Character::getName() const
{
	return(name);
}
void				Character::equip(AMateria* m)
{
	if (m == 0)
	{
		std::cout << "illegitimate object \n";
		return;
	}
	if (InvAmount >= 4)
	{
		std::cout << "inventory is full \n";
		return;
	}
	inventory[InvAmount] = m;
	std::cout << m->getType() << " Added to inventory \n";
	InvAmount++;
	return;
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
	if (inventory[idx])
	{
		inventory[idx]->use(target);
		std::cout << idx << std::endl;
	}
}	
