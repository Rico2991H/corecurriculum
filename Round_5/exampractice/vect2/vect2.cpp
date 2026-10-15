#include "vect2.hpp"
#include "sstream"
//constructors

vect2::vect2() : x(0) , y(0)
{

}
vect2::vect2(int x, int y) : x(x) , y(y)
{}
vect2::vect2(const vect2& other)
{
	*this = other;
}

//operator overloads

vect2& vect2::operator=(const vect2& other)
{
	if (this != &other)
	{
		this->x = other.x;
		this->y = other.y;
	}
	return (*this);
}

int&		vect2::operator[](int idx)
{
	if (idx == 0)
		return this->x;
	else
		return this->y;
}

int		vect2::operator[](const int idx) const
{
	if (idx == 0)
		return this->x;
	else
		return this->y;
}

vect2	vect2::operator+(const vect2& other) const
{
	vect2 result;
	result.x = this->x + other.x;
	result.y = this->y + other.y;
	return result;
}

vect2&	vect2::operator+=(const vect2& other)
{
	this->x = this->x + other.x;
	this->y = this->y + other.y;
	return (*this);
}

vect2	vect2::operator-(const vect2& other) const
{
	vect2 result;
	result.x = this->x - other.x;
	result.y = this->y - other.y;
	return result;
}

vect2&	vect2::operator-=(const vect2& other)
{
	this->x = this->x - other.x;
	this->y = this->y - other.y;
	return (*this);
}

vect2	vect2::operator*(const vect2& other)
{
	vect2 result;
	result.x = this->x * other.x;
	result.y = this->y * other.y;
	return result;
}

vect2&	vect2::operator*=(const vect2& other)
{
	this->x = this->x * other.x;
	this->y = this->y * other.y;
	return (*this);
}

vect2	vect2::operator*(const int val) const
{
	vect2 result;
	result.x = this->x * val;
	result.y = this->y * val;
	return result;
}

vect2&	vect2::operator*=(int val)
{
	this->x = this->x * val;
	this->y = this->y * val;
	return (*this);
}

bool	vect2::operator==(const vect2& other) const
{
	if (this->x != other.x)
		return false;
	if (this->y != other.y)
		return false;
	return true;
}

bool	vect2::operator!=(const vect2& other) const
{
	if (this->x != other.x)
		return true;
	if (this->y != other.y)
		return true;
	return false;
}

vect2&	vect2::operator++()
{
	this->x += 1;
	this->y += 1;
	return (*this);
}

vect2	vect2::operator++(int)
{
	vect2 result;
	result = *this;
	this->x += 1;
	this->y += 1;
	return (result);
}

vect2&	vect2::operator--()
{
	this->x -= 1;
	this->y -= 1;
	return (*this);
}

vect2	vect2::operator--(int)
{
	vect2 result;
	result = *this;
	this->x -= 1;
	this->y -= 1;
	return (result);
}


//destructor

vect2::~vect2(){}

//setters

void	vect2::set_x(int x)
{
	this->x = x;
}

void	vect2::set_y(int y)
{
	this->y = y;
}

//getters

int		vect2::get_x() const
{
	return (x);
}

int		vect2::get_y() const
{
	return (y);
}
// non-member


std::ostream& operator<<(std::ostream& os, const vect2& obj)
{
	os << "{" << obj.get_x() << ", " << obj.get_y() << "}" << std::endl;
	return (os);
}

vect2	operator*(int val, vect2& other)
{
	vect2 result;
	result.set_x(val * other.get_x());
	result.set_y(val * other.get_y());
	return result;
}

vect2	vect2::operator-() const
{
	vect2 result;
	result.set_x(-this->x);
	result.set_y(-this->y);
	return (result);
}

int main()
{
	vect2 v1(1, 2); // 1, 2
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v1: " << "{" << v1[0] << ", " << v1[1] << "}" << std::endl;
	vect2 v1; // 0, 0
	vect2 v2(1, 2); // 1, 2
	const vect2 v3(v2); // 1, 2
	vect2 v4 = v2; // 1, 2
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v1: " << "{" << v1[0] << ", " << v1[1] << "}" << std::endl; //should be the same as the line above
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "v3: " << v3 << std::endl;
	std::cout << "v4: " << v4 << std::endl;
	std::cout << v4++ << std::endl; // 2, 3
	std::cout << ++v4 << std::endl; // 3, 4
	std::cout << v4-- << std::endl; // 2, 3
	std::cout << --v4 << std::endl; // 1, 2
	v2 += v3; // 2, 4
	v1 -= v2; // -2, -4
	v2 = v3 + v3 * 2; // 3, 6
	v2 = 3 * v2; // 9, 18
	v2 += v2 += v3; // 20, 40
	v1 *= 42; // -84, -168
	v1 = v1 - v1 + v1;
	std::cout << "v1: " << v1 << std::endl;
	std::cout << "v2: " << v2 << std::endl;
	std::cout << "-v2: " << -v2 << std::endl;
	std::cout << "v1[1]: " << v1[1] << std::endl;
	v1[1] = 12;
	std::cout << "v1[1]: " << v1[1] << std::endl;
	std::cout << "v3[1]: " << v3[1] << std::endl;
	std::cout << "v1 == v3: " << (v1 == v3) << std::endl;
	std::cout << "v1 == v1: " << (v1 == v1) << std::endl;
	std::cout << "v1 != v3: " << (v1 != v3) << std::endl;
	std::cout << "v1 != v1: " << (v1 != v1) << std::endl;
}