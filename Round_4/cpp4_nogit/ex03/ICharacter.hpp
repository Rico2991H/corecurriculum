#ifndef ICHARACTER_HPP
#define ICHARACTER_HPP

#include <string>
#include <iostream>
#include "AMateria.hpp"

class AMateria;

class ICharacter
{
	public:
		ICharacter();
		ICharacter(std::string input);
		ICharacter(const ICharacter& other);
		ICharacter& operator=(const ICharacter& other);
		virtual 					~ICharacter();
		virtual std::string const&	getName() const = 0;
		virtual void				equip(AMateria* m) = 0;
		virtual void 				unequip(int idx) = 0;
		virtual void				use(int idx, ICharacter& target ) = 0; 
	private:
		
	protected:
		std::string name;
		AMateria	*inventory[4];
		int			InvAmount;

};

#endif
