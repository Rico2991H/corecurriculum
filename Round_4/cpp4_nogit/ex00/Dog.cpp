/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:15:58 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/27 11:30:29 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include <string>
#include <iostream>

Dog::Dog() : Animal()
{
	type = "Dog";
	std::cout << "Dog Constructor called\n";
}

Dog::Dog(const Dog& other) : Animal(other)
{
	std::cout << "Dog Copy consturctor called\n";
}

Dog& Dog::operator=(const Dog& other)
{
	std::cout << "Dog Copy assignment operator called\n";
	if(this != &other)
	{
		Animal::operator=(other);
	}
	return (*this);
}

void Dog::makeSound() const
{
	std::cout << "WOEF WOEF" << std::endl;
}

Dog::~Dog()
{
    std::cout << "Dog Destructor called\n";
}
