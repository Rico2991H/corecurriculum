/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:26:12 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 10:23:48 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <string>
#include <iostream>

Zombie::Zombie()
{ 
}

Zombie::~Zombie()
{
    std::cout << "Destroyed:" << this->getName() << std::endl;
}

void Zombie::setName(std::string input)
{
    name = input;   
}

std::string Zombie::getName() const {return name;}

void    Zombie::announce(void) const
{
    std::cout << name << ":" << "BraiiiiiiinnnzzzZ..." << std::endl;
}
