/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:05:45 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/03 12:12:23 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Phonebook.hpp"
#include <limits>

std::string truncate(std::string str)
{
	if (str.length() > 9)
		return(str.substr(0, 9) + ".");
	return (str);
}

void WaitForEnter()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::string dummy;
	std:: cout << "Press enter to return \n";
	std::getline(std::cin, dummy);		
}

void	Phonebook::AddContact(Contact NewC)
{
	int i = 0;

	if (No_C != 8)
	{
		cons[No_C] = NewC;
		cons[No_C].setIndex(No_C);
		No_C++;
	}
	else
	{
		while(i < 7)
		{
			cons[i] = cons[i+1];
			cons[i].setIndex(i);
			i++;
		}
		cons[i] = NewC;
	}
	std::cout << "Successfully added contact\n";
}

void	Phonebook::DisplayContact(Contact C)
{
	std::string	input = "";

	std::cout << std::setw(10) << "First name: ";
	std::cout << C.getFname() << std::endl;
	std::cout << std::setw(10) << "Last name: ";
	std::cout << C.getLname() << std::endl;
	std::cout << std::setw(10) << "Nickname: ";
	std::cout << C.getNname() << std::endl;
	std::cout << std::setw(10) << "Phonenumber: ";
	std::cout << C.getPnumber() << std::endl;
	std::cout << std::setw(10) << "Darkest secret: ";
	std::cout << C.getD_secret() << std::endl;
}

void	Phonebook::AskContactInput()
{
	int			i = 0;
	std::string	input = "";

	std:: cout << "Type the index number to display contact" << std:: endl;
	std:: cout << "Type return to go to the main menu" << std:: endl;
	if (!(std:: cin >> input))
	{
		if (std::cin.eof()) 
			return;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	if (input == "return")
		return;
	if (isdigit(input[i]))
	{
		int	index;
		std::istringstream ss(input); // changes normal string to input string stream
		if (!(ss >> index))
		{
			std::cout << "Index value out of range" << std::endl;
			return;
		}
		while (i < 8)
		{
			if (index == cons[i].getIndex())
			{
				DisplayContact(cons[i]);
				WaitForEnter();
				return;				
			}
			i++;
		}
		std::cout << "Contact not found." << std::endl;		
	}
}

void	Phonebook::Display()
{
	int			i = 0;
	std::string	input = "";

	std:: cout << "|";
	std::cout << std::right << std::setw(10) << "index";
	std:: cout << "|";
	std::cout << std::right << std::setw(10) << "first name";
	std:: cout << "|";
	std::cout << std::right << std::setw(10) << "last name";
	std:: cout << "|";
	std::cout << std::right << std::setw(10) << "nickname";
	std:: cout << "|" << std:: endl;
	while(i < No_C)
	{
		std:: cout << "|";
		std::cout << std::right << std::setw(10) << cons[i].getIndex();
		std:: cout << "|";
		std::cout << std::right << std::setw(10) << truncate(cons[i].getFname());
		std:: cout << "|";
		std::cout << std::right << std::setw(10) << truncate(cons[i].getLname());
		std:: cout << "|";
		std::cout << std::right << std::setw(10) << truncate(cons[i].getNname());
		std:: cout << "|" << std:: endl;
		i++;	
	}
}