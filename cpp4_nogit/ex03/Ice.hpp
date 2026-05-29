#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <string>
#include <iostream>

class Ice : public AMateria
{
	public:
		Ice();
		Ice(const Ice& other);
		Ice& operator=(const Ice& other);
		~Ice();
		AMateria*	clone() const;
		void		use(ICharacter& target);

	private:

	protected:
};

#endif
