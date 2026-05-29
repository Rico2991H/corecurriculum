/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:15:58 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 13:16:38 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Brain.hpp"
#include <string>
#include <iostream>

Dog::Dog() : Animal(), dogBrain(new Brain())
{
	type = "Dog";
	std::cout << "Dog Constructor called\n";
}

Dog::Dog(const Dog& other) : Animal(other), dogBrain(new Brain(*other.dogBrain))
{
	std::cout << "Dog Copy consturctor called\n";
}

Dog& Dog::operator=(const Dog& other)
{
	std::cout << "Dog Copy assignment operator called\n";
	if(this != &other)
	{
		Animal::operator=(other);
		delete this->dogBrain;
		this->dogBrain = new Brain(*other.dogBrain);
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
	delete this->dogBrain;
}
