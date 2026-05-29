/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:30:42 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/01 10:41:04 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include <string>
#include <iostream>

AMateria::AMateria()
{
	std::cout << "Def Constructor called\n";
}

AMateria::AMateria(const AMateria& other)
{
	*this = other;
	std::cout << "Copy constructor called\n";
}

AMateria&  AMateria::operator=(const AMateria& other)
{
	std::cout << "Copy assignment operator called\n";
	if(this != &other)
	{
		this->type = other.type;
	}
	return (*this);
}

AMateria::~AMateria()
{
    std::cout << "AMateria Destructor called\n";
}

void				AMateria::setType(std::string input)
{
	type = input;
}

std::string const&	AMateria::getType() const { return (type); }
		
/*const AMateria* AMateria::clone() const
{
		return (this);
}
void		AMateria::use(ICharacter& target)
{
	(void)target;
}*/
