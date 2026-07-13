/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:11:42 by rhoogend          #+#    #+#             */
/*   Updated: 2026/06/01 11:06:25 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Brain.hpp"
#include <string>
#include <iostream>


Cat::Cat() : Animal("Cat"), catBrain(new Brain())
{
	std::cout << "Cat Constructor called\n";
}

Cat::Cat(const Cat& other) : Animal(other), catBrain(new Brain(*other.catBrain))
{
	std::cout << "Cat Copy constructor called\n";
}

Cat& Cat::operator=(const Cat& other)
{
	std::cout << "Cat Copy assignment operator called\n";
	if(this != &other)
	{
		Animal::operator=(other);
		delete this->catBrain;
		catBrain = new Brain(*other.catBrain);
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
	delete this->catBrain;
}
