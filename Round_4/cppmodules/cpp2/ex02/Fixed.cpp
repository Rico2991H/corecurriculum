/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:16:17 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/24 12:17:49 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <iostream>
#include <string>
#include <cmath>

const int Fixed::f_bits = 8;

Fixed::Fixed(void) : value(0) 
{
}

Fixed::Fixed(int const nb)
{
	value = nb << f_bits;	
}

Fixed::Fixed(float const nb)
{	
	value = roundf(nb * (1 << f_bits));
}

Fixed::Fixed(const Fixed& other)
{
	*this = other;
}

Fixed& Fixed::operator=(const Fixed& other)
{
	if(this != &other)
		value = other.getRawBits();
	return (*this);
}

Fixed Fixed::operator+(const Fixed& other)
{
	Fixed	newfix;
	newfix.setRawBits(this->getRawBits() + (long)other.getRawBits());
	return (newfix);
}

Fixed Fixed::operator-(const Fixed& other)
{
	Fixed	newfix;
	newfix.setRawBits(this->getRawBits() + (long)other.getRawBits());
	return (newfix);
}

Fixed Fixed::operator*(const Fixed& other)
{
	Fixed	newfix;
	long temp = ((long)this->getRawBits() * (long)other.getRawBits() >> f_bits);
	newfix.setRawBits((int)temp);
	return (newfix);
}

Fixed Fixed::operator/(const Fixed& other)
{
	Fixed	newfix;
	long temp = ((long)this->getRawBits() << f_bits) / (long)other.getRawBits();
	newfix.setRawBits((int)temp);
	return (newfix);
}

std::ostream& operator<<(std::ostream& os, const Fixed& obj)
{
	os << obj.toFloat();
	return os;
}

bool Fixed::operator>(const Fixed& other) const
{
	return (this->value > other.value);
}

bool Fixed::operator<(const Fixed& other) const
{
	return (this->value < other.value);	
}

bool Fixed::operator>=(const Fixed& other) const
{
	return (this->value >= other.value);
}

bool Fixed::operator<=(const Fixed& other) const
{
	return (this->value <= other.value);	
}

bool Fixed::operator==(const Fixed& other) const
{
	return (this->value == other.value);	
}

bool Fixed::operator!=(const Fixed& other) const
{
	return (this->value != other.value);	
}

Fixed&	Fixed::operator++()
{
	++value;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed tmp = *this;
	++value;
	return tmp;
}

Fixed&	Fixed::operator--()
{
	--value;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed tmp = *this;
	--value;
	return tmp;	
}
Fixed&	Fixed::min(Fixed& left, Fixed& right)
{
	if (left.getRawBits() > right.getRawBits())
		return (right);
	else
		return (left);
}

const Fixed&	Fixed::min(const Fixed& left,const Fixed& right)
{
	if (left.getRawBits() > right.getRawBits())
		return (right);
	else
		return (left);	
}

Fixed&	Fixed::max(Fixed& left, Fixed& right)
{
	if (left.getRawBits() < right.getRawBits())
		return (right);
	else
		return (left);
}
const Fixed&	Fixed::max(const Fixed& left,const Fixed& right)
{
	if (left.getRawBits() < right.getRawBits())
		return (right);
	else
		return (left);
}

Fixed::~Fixed()
{
}

int	Fixed::getRawBits(void) const
{
	return(this->value);
}

void	Fixed::setRawBits(int const raw)
{
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