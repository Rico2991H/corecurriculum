/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IMateriaSource.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:01:55 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/01 10:45:08 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IMateriaSource.hpp"

IMateriaSource::IMateriaSource()
{
	std::cout << "Constructor called\n";
}

IMateriaSource::IMateriaSource(const IMateriaSource& other)
{
	*this = other;
	std::cout << "Copy consturctor called\n";
}

IMateriaSource& IMateriaSource::operator=(const IMateriaSource& other)
{
	std::cout << "Copy assignment operator called\n";
	if(this != &other)
	{
		*this = other;
	}
	return (*this);
}

IMateriaSource::~IMateriaSource()
{
    std::cout << "Destructor called\n";
}
/*void		learnMateria(AMateria*)
{

}
AMateria*	createMateria(std::string const& type)
{
	
}*/