/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newZombie.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:23:19 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 10:14:51 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie *newZombie(std::string name ) // This zombie will be  added to the stack.
{
    Zombie *New = new Zombie(name);
    New->announce();
    return (New);
}


