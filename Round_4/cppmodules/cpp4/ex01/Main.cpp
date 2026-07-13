/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 10:45:09 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/31 09:37:23 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Brain.hpp"

int	main()
{
	Animal *Animals[10];
	for (int i = 0; i < 10 ;i++)
	{
		if (i % 2 == 0)
			Animals[i] = new Dog();
		else
			Animals[i] = new Cat();
	};
	for (int i = 0; i < 10; i++)
		delete Animals[i];
}