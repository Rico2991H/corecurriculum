#ifndef VECT2_HPP
#define VECT2_HPP

#include "iostream"
#include "string"
#include "sstream"

class vect2
{
	public:
		//constructors
		vect2();
		vect2(int x, int y);
		vect2(const vect2& other);
		//operator overloads
		vect2&	operator=(const vect2& other);
		int&	operator[](int idx);
		int		operator[](int idx) const;
		vect2&	vect2::operator++();
		vect2	vect2::operator++(int);
		vect2&	vect2::operator--();
		vect2	vect2::operator--(int);
		vect2	operator+(const vect2& other) const;
		vect2&	operator+=(const vect2& other);
		vect2	operator*(const vect2& other);
		vect2&	operator*=(const vect2& other);
		vect2	operator*(const int val) const;
		vect2&	operator*=(int val);
		vect2	operator-(const vect2& other) const;
		vect2	operator-() const;
		vect2&	operator-=(const vect2& other);
		bool	operator==(const vect2& other) const;
		bool	operator!=(const vect2& other) const;

		//destructor
		~vect2();
		//setters
		void	set_x(int x);
		void	set_y(int y);
		//getters
		int		get_x() const;
		int		get_y() const;


	private:
		int x;
		int y;
};

std::ostream& operator<<(std::ostream& os, const vect2& obj);

#endif