/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:42:41 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/31 16:20:37 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

#include <string>
#include <iostream>

Ice::Ice()
{
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
const AMateria*	Ice::clone() const
{
	AMateria *NewCure = new Ice();
	std::cout << "Cloning ice \n";
	return (NewCure);
}
void		Ice::use(ICharacter& target)
{
	(void)target;
}