/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:01:18 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/12 15:47:09 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>

#ifndef _CONTACT_H_
#define _CONTACT_H_

class Contact
{
	public:
		int				PhoneNumber = 0;
		std::string		D_Secret;
		void 			init_contact(void);
		void			setIndex(int i);
		std::string		getLname();
		int				getIndex();
		std::string		getFname();
		std::string		getNname();
		
	private:
		std::string F_Name;
		std::string	L_Name;
		std::string	NickName;
		int			Index = 0;
};

#endif