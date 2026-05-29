#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include <string>
#include <iostream>
#include "IMateriaSource.hpp"

class AMateria;

class MateriaSource : public IMateriaSource
{
	public:
		MateriaSource();
		MateriaSource(const MateriaSource& other);
		MateriaSource& operator=(const MateriaSource& other);
		~MateriaSource();
		void		learnMateria(AMateria*);
		AMateria*	createMateria(std::string const& type);

	private:
		AMateria	*inventory[4];
};

#endif
