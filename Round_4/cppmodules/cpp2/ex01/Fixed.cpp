/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:16:17 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/23 13:42:11 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <string>
#include <cmath>

const int Fixed::f_bits = 8;

Fixed::Fixed(void) : value(0) 
{
	std::cout << "Def Constructor called\n";
}

Fixed::Fixed(int const nb)
{
	std::cout << "int to fixed constr called" << std::endl;
	value = nb << f_bits;	
}

Fixed::Fixed(float const nb)
{	

	std::cout << "float to fixed constr called" << std::endl;
	value = roundf(nb * (1 << f_bits));
}

Fixed::Fixed(const Fixed& other)
{
	std::cout << "Copy constructor called\n";
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	std::cout << "Copy assignment operator called\n";
	if(this != &other)
		value = other.getRawBits();
	return (*this);
}

std::ostream& operator<<(std::ostream& os, const Fixed& obj)
{
	os << obj.toFloat();
	return os;
}

Fixed::~Fixed()
{
	std::cout << "Def Destructor called\n";
}

int	Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return(this->value);
}

void	Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	this->value = raw;
}

float	Fixed::toFloat(void) const
{
	float f_value;
	f_value = (float)value / (1 << f_bits);
	return(f_value);
}

int		Fixed::toInt(void) const
{
	return (value >> f_bits);	
}