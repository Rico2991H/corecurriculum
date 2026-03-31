/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 13:45:29 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/27 14:15:37 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "WrongCat.hpp"
#include "WrongAnimal.hpp"
#include <string>
#include <iostream>


WrongCat::WrongCat() : WrongAnimal()
{
	type = "Cat";
	std::cout << "Cat Constructor called\n";
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other)
{
	std::cout << "Cat Copy constructor called\n";
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	std::cout << "Copy assignment operator called\n";
	if(this != &other)
	{
		WrongAnimal::operator=(other);
	}
	return (*this);
}

void WrongCat::makeSound() const
{
	std::cout << "MEEOOUWW" << std::endl;
}

WrongCat::~WrongCat()
{
    std::cout << "Cat Destructor called\n";
}