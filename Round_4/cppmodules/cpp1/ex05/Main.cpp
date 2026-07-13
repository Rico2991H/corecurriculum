/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:05:01 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/19 14:56:26 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"
#include <iostream>
#include <string>

int	main()
{
	Harl Harl1;
	std:: string level;
	std::cin >> level;
	Harl1.complain(level);
}
