/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:10:07 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/01 14:43:03 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iomanip>
#include "Contact.hpp"

#ifndef _PHONEBOOK_H_
#define _PHONEBOOK_H_

class Phonebook
{
	private:
		Contact cons[8];
		int		No_C;
	public:
		void	AddContact(Contact NewC);
		void	DisplayContact(Contact C);
		void	AskContactInput();
		void	Display();
		Phonebook() : No_C(0) {}
};

#endif

