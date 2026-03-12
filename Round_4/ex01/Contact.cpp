/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 13:35:56 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/12 17:31:37 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Contact.hpp"

void Contact::setIndex(int i)
{
	Index = i;
}

std::string Contact::getFname() { return F_Name; }
int 		Contact::getIndex() { return Index; }
std::string Contact::getNname() { return NickName; }
std::string Contact::getLname() { return L_Name; }

void Contact::init_contact(void)
{
	std::string input = "";
	std::cout << "Input first name:\n";
	std::getline(std::cin, F_Name);
	std::cout << "Input last name:\n";
	std::getline(std::cin, L_Name);
	std::cout << "Input Nickname:\n";
	std::getline(std::cin, NickName);
	std::cout << "Input Darkest secret:\n";
	std::getline(std::cin, D_Secret);
	std::cout << "Input Phonenumber:\n";
	std::getline(std::cin, input);
	PhoneNumber = std::stoi(input);
	return; 
}
