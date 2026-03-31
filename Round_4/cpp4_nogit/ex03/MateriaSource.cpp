/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:08:19 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/31 14:31:35 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include <string>
#include <iostream>

MateriaSource::MateriaSource()
{
	std::cout << "Constructor called\n";
}

MateriaSource::MateriaSource(const MateriaSource& other)
{
	std::cout << "Copy consturctor called\n";
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
	std::cout << "Copy assignment operator called\n";
	if(this != &other)
	{
	}
	return (*this);
}

MateriaSource::~MateriaSource()
{
    std::cout << "Destructor called\n";
}

void		learnMateria(Amateria*)
{
	
}

Amateria*	createMateria(std::string const& type)
{
	
}
