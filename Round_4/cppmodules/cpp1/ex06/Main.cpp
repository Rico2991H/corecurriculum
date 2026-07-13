/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:05:01 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/19 16:47:16 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>
#include <string>

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		Harl Harl1;
		std::string level;
		level = argv[1];
		Harl1.complain(level);
	}
	else
		std::cout << "program requires exactly one arg" << std::endl;
		
}
