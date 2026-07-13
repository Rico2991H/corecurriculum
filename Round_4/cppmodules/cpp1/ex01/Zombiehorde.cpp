/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombiehorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:05:59 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 10:26:38 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <string>
#include <iostream>

Zombie *ZombieHorde(std::string name, int N)
{
	int i = 0;
	Zombie* horde = new Zombie[N];
	for(i = 0; i < N; i++)
	{
    	horde[i].setName(name);
		horde[i].announce();
	}
	return (horde);
}