/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:01:18 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/01 14:44:30 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <limits>
#include <sstream>

#ifndef _CONTACT_H_
#define _CONTACT_H_

class Contact
{
	public:
		int 			init_contact(void);
		void			setIndex(int i);
		std::string		getLname();
		int				getIndex();
		std::string		getFname();
		std::string		getNname();
		int				getPnumber();
		std::string		getD_secret();
		Contact() : PhoneNumber(0), Index(0) {}
		
	private:
		int				PhoneNumber;
		std::string		D_Secret;
		std::string F_Name;
		std::string	L_Name;
		std::string	NickName;
		int			Index;
};

#endif