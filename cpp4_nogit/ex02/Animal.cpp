/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:06:44 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/31 10:36:15 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Animal.hpp"
#include <iostream>
#include <string>

Animal::Animal() : type("default")
{
	std::cout << "Constructor called\n";
}

Animal::Animal(const Animal& other) : type(other.type)
{
	std::cout << "Copy constructor called\n";
}

Animal& Animal::operator=(const Animal& other)
{
	std::cout << "Animal Copy assignment operator called\n";
	if(this != &other)
	{
		type = other.type;
	}
	return (*this);
}

Animal::~Animal()
{
    std::cout << "Destructor called\n";
}
std::string	Animal::getType() const { return (type); }


void	Animal::makeSound() const
{
	std::cout << "MEWOEOW im still deciding whats my type.." << std::endl;
}