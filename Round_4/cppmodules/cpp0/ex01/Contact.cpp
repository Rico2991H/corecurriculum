/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:35:56 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/08 11:32:12 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Contact.hpp"

void Contact::setIndex(int i)
{
	Index = i;
}

std::string Contact::getFname() { return (F_Name); }
int 		Contact::getIndex() { return (Index); }
std::string Contact::getNname() { return (NickName); }
std::string Contact::getLname() { return (L_Name); }
int			Contact::getPnumber() {return (PhoneNumber);}
std::string	Contact::getD_secret() {return (D_Secret);}

bool	IsNumeric(std::string input)
{
	int	i = 0;
	while(input[i])
	{
		if (!isdigit(input[i]))
		{
			std::cout << "Input error: Non numeric value detected" << std::endl;
			return(false);
		}
		i++;
	}
	return (true);
}

bool check_init_contact(std::string &condetail, std::string input)
{
	while(true)
	{
		if(!getline(std::cin, condetail))
			return false;
		if(!condetail.empty())
			return true;
		std::cout << "Field cannot be empty\n";
		std::cout << input;
	}

}
int Contact::init_contact(void)
{
	std::string input = "";
	std::cout << "Input first name:\n";
	check_init_contact(F_Name, "Input first name:\n");
	std::cout << "Input last name:\n";
	check_init_contact(L_Name, "Input last name:\n");
	std::cout << "Input Nickname:\n";
	check_init_contact(NickName,"Input Nickname:\n");
	std::cout << "Input Darkest secret:\n";
	check_init_contact(D_Secret, "Input Darkest secret:\n");
	std::cout << "Input Phonenumber:\n";
	check_init_contact(input, "Input Phonenumber:\n");
	if (!IsNumeric(input))
		return (false);
	std::istringstream ss(input);
	if (!(ss >> PhoneNumber))
	{
		std::cout << "Phonenumber value out of range" << std::endl;
		return (false);
	}
	return (true); 
}
