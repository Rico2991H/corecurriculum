/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:41:30 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/31 16:16:58 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"
#include <string>
#include <iostream>

Cure::Cure() : AMateria()
{
	std::cout << "Constructor called\n";
}

Cure::Cure(const Cure& other) : AMateria(other)
{
	std::cout << "Copy consturctor called\n";
}

Cure& Cure::operator=(const Cure& other)
{
	std::cout << "Copy assignment operator called\n";
	if(this != &other)
	{
		AMateria::operator=(other);
	}
	return (*this);
}

Cure::~Cure()
{
    std::cout << "Destructor called\n";
}

const AMateria* Cure::clone() const
{
	AMateria *NewCure = new Cure();
	std::cout << "Cloning cure \n";
	return (NewCure);
}
void		Cure::use(ICharacter& target)
{
	(void)target;
}