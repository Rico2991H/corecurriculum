/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 13:07:55 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/31 17:31:18 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <string>
#include <iostream>
#include "ICharacter.hpp"

class Character : public ICharacter
{
	public:
		Character();
		Character(std::string input);
		Character(const Character& other);
		Character& operator=(const Character& other);
		~Character();
		std::string const&	getName() const;
		void				equip(AMateria* m);
		void 				unequip(int idx);
		void				use(int idx, ICharacter& target ); 

	private:
};

#endif
