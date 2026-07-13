/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:24:22 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 10:16:53 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Zombie.hpp"

Zombie::Zombie(std::string input) : name(input)
{ 
}

Zombie::~Zombie()
{
    std::cout << "Destroyed:" << getName() << std::endl;
}

std::string Zombie::getName() const {return name;}

void    Zombie::announce( void ) const
{
    std::cout << name << ":" << "BraiiiiiiinnnzzzZ..." << std::endl;
}

int main()
{
    std::string name = "igor";
    std::string name2 = "stein";
    Zombie *igor = newZombie(name); //this zombie will be stored in the heap
    randomChump(name2); // this zombie will be stored in the stack
    delete igor;
    return (0);
}