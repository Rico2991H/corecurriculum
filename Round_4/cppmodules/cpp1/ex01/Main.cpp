/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:02:28 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 10:22:51 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"
#include <string>
#include <iostream>

void	extra_test(std::string input, int n)
{
	Zombie *horde = ZombieHorde(input, n);
	delete[] horde;
}

int main()
{
	int	n = 7;
    std::string name = "igor";
    std::string name2 = "stein";
	Zombie *horde = ZombieHorde( name2, n);
	delete[] horde;
	std::cout << "test with 0 zombies \n";
	extra_test("Alfred", 0);
	std::cout<< "test with 25 zombies \n";
	extra_test("Many", 25);
    return (0);
}