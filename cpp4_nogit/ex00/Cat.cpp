/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:11:42 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 12:22:37 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include <string>
#include <iostream>


Cat::Cat() : Animal()
{
	type = "Cat";
	std::cout << "Cat Constructor called\n";
}

Cat::Cat(const Cat& other) : Animal(other)
{
	type = other.type;
	std::cout << "Cat Copy constructor called\n";
}

Cat& Cat::operator=(const Cat& other)
{
	std::cout << "Cat Copy assignment operator called\n";
	if(this != &other)
	{
		Animal::operator=(other);
	}
	return (*this);
}

void Cat::makeSound() const
{
	std::cout << "MEEOOUWW" << std::endl;
}

Cat::~Cat()
{
    std::cout << "Cat Destructor called\n";
}
