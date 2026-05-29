/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:31:24 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/01 12:12:46 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>
#include <iostream>

class ICharacter;

class AMateria
{
	public:
		virtual ~AMateria();
		AMateria &operator=(const AMateria& other);
		void					setType(std::string input);
		std::string const&		getType() const; 
		virtual AMateria* clone() const = 0;
		virtual	void			use(ICharacter& target) = 0;

	protected:
		std::string type;
		AMateria();
		AMateria(const AMateria& other);

		
};

#endif
