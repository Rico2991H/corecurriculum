/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:42:41 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/01 12:13:29 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

#include <string>
#include <iostream>

Ice::Ice()
{
	this->setType("ice");
	std::cout << "Ice Constructor called\n";
}

Ice::Ice(const Ice& other) : AMateria(other)
{
	std::cout << "Ice Copy constructor called\n";
}

Ice& Ice::operator=(const Ice& other)
{
	std::cout << "Copy assignment operator called\n";
	if(this != &other)
		AMateria::operator=(other);
	return (*this);
}

Ice::~Ice()
{
    std::cout << "Destructor called\n";
}
AMateria*	Ice::clone() const
{
	AMateria *NewCure = new Ice();
	std::cout << "Cloning ice \n";
	return (NewCure);
}
void		Ice::use(ICharacter& target)
{
	std::cout << "Ice:" << "* shoots an ice bolt at " << target.getName() << "*\n";
}