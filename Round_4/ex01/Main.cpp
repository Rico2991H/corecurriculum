/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 12:44:56 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/12 17:26:03 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Main.hpp"

void	init_prompt(Phonebook *PB) //function to propmpt for ADD/SEARCH/EXIT 
{
	char	input;
	
	std::cout << "To add contact type A and enter:\n";
	std::cout << "To search type S and enter:\n";
	std::cout << "To exit type E and enter:\n";
	std::cin >> input;
	std::cin.ignore();
	switch 	(input)
	{
		case 'A':
		{
			Contact NewC;
			NewC.init_contact();
			PB->AddContact(NewC);
			break;
		}
		case 'S':
		{
			PB->Display();
			PB->AskContactInput();
			break;
		}
		case 'E':
			exit(0);
	}
	init_prompt(PB);
}

int main()
{
	Phonebook newPB;
	
	init_prompt(&newPB);
}