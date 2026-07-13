/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 15:59:52 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/17 16:27:41 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int	main()
{
	std::string str1 = "HI THIS IS BRAIN";
	std::string *ptr1 = &str1;
	std::string &ref1 = str1; 

	std::cout << "adresses:" << std::endl;
	std::cout << &str1 << std::endl;
	std::cout << ptr1 << std::endl;
	std::cout << &ref1 << std::endl;

	std::cout << "values:" << std::endl;
	std::cout << str1 << std::endl;
	std::cout << *ptr1 << std::endl;
	std::cout << ref1 << std::endl;
	return(0);
}

