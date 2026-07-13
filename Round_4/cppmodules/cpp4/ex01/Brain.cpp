/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 14:25:56 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/31 09:27:30 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"
#include <string>
#include <iostream>

Brain::Brain()
{
	std::cout << "Brain constructor called\n";
}

Brain::Brain(const Brain& other)
{
	*this = other;
	std::cout << "Copy constructor called\n";
}

Brain& Brain::operator=(const Brain& other)
{
	int n = sizeof(ideas)/sizeof(ideas[0]);
	std::cout << "Brain Copy assignment operator called\n";
	if(this != &other)
	{
		for (int i = 0; i < n; i++)
			this->ideas[i] = other.ideas[i];
	}
	return (*this);
}

Brain::~Brain()
{
    std::cout << "Brain Destructor called\n";
}
