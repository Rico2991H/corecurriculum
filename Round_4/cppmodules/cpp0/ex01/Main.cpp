/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:44:56 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/03 11:57:06 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cctype>
#include <iostream>
#include <cstdlib>
#include "Contact.hpp"
#include "Phonebook.hpp"

void	init_prompt(Phonebook *PB)
{
	std::string	input;

	while(true)
	{
		std::cout << "To add contact type ADD and enter:\n";
		std::cout << "To search type SEARCH and enter:\n";
		std::cout << "To exit type EXIT and enter:\n";
		if (!(std:: cin >> input))
		{
			if (std::cin.eof())
        	{
				std::cout << "EOF detected, exiting\n";
				break;
        	}
			std::cin.clear(); 
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (input == "ADD")
		{
			Contact NewC;
			if (NewC.init_contact())
				PB->AddContact(NewC);
		}
		else if (input == "SEARCH")
		{
			PB->Display();
			PB->AskContactInput();
		}
		else if (input == "EXIT")
			return;
	}
}

int main()
{
	Phonebook newPB;
	
	init_prompt(&newPB);
}
