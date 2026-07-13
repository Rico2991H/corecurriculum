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
		Fixed& 	operator=(const Fixed& other);
		Fixed 	operator+(const Fixed& other);
		Fixed 	operator-(const Fixed& other);
		Fixed 	operator*(const Fixed& other);
		Fixed 	operator/(const Fixed& other);
		bool 	operator>(const Fixed& other) const;
		bool 	operator<(const Fixed& other) const;
		bool 	operator>=(const Fixed& other) const;
		bool 	operator<=(const Fixed& other) const;
		bool 	operator==(const Fixed& other) const;
		bool 	operator!=(const Fixed& other) const;
		Fixed&	operator++();
		Fixed	operator++(int nb);
		Fixed&	operator--();
		Fixed	operator--(int nb);
		static Fixed&		min(Fixed& left, Fixed& right);
		static const Fixed&	min(const Fixed& left,const Fixed& right);
		static Fixed&		max(Fixed& left, Fixed& right);
		static const Fixed&	max(const Fixed& left,const Fixed& right);
		~Fixed();

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;
		int					value;

	private:
		//int					value;
		static const int	f_bits;
};

std::ostream& operator<<(std::ostream& os, const Fixed& obj);

#endif
