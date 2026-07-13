#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <string>

class Fixed
{
	public:
		Fixed(void);
		Fixed(int const nb);
		Fixed(float const nb);
		Fixed(const Fixed& other); // takes a constant floating point number and converts it. 
		Fixed& operator=(const Fixed& other);
		~Fixed();
		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;

	private:
		int					value;
		static const int	f_bits;
};

std::ostream& operator<<(std::ostream& os, const Fixed& obj);

#endif
