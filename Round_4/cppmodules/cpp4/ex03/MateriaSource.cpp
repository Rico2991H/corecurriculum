/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:08:19 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/01 13:56:11 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"
#include <string>
#include <iostream>

MateriaSource::MateriaSource()
{
	InvAmount = 0;
	std::cout << "Constructor called\n";
}

MateriaSource::MateriaSource(const MateriaSource& other) : IMateriaSource(other)
{
	std::cout << "MSource copy consturctor called\n";
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
	std::cout << "Copy assignment operator called\n";
	if(this != &other)
	{
		IMateriaSource::operator=(other);
	}
	return (*this);
}

MateriaSource::~MateriaSource()
{
	for (int i = 0 ; i < 4 ; i++)
	{
		if(inventory[i])
			delete inventory[i];
	}
    std::cout << "Destructor called\n";
}
/*Copies the Materia passed as a parameter and stores it in memory so it can be cloned
later. Like the Character, the MateriaSource can know at most 4 Materias. They
are not necessarily unique.*/
void		MateriaSource::learnMateria(AMateria* AM)
{
    if (!AM)
        return;

    if (this->InvAmount >= 4)
        return;

    this->inventory[this->InvAmount] = AM;
    std::cout << "adding at slot " << this->InvAmount << std::endl;
    this->InvAmount++;
}

AMateria*	MateriaSource::createMateria(std::string const& type)
{
	for (int i = 0; i < 4; i++)
	{
        if (this->inventory[i] && this->inventory[i]->getType() == type)
        {
            return (this->inventory[i]->clone());
        }
	}
	return (0);
}
