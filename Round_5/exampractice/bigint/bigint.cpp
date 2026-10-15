#include "bigint.hpp"

std::string reverse(std::string reversed)
{
	std::string unreversed;
	for(std::string::reverse_iterator i = reversed.rbegin(); i != reversed.rend(); i++)
	{
		unreversed.push_back(*i);
	}
	return (unreversed);
}

void equalize_size(std::string *shorter, std::string *longer)
{
	int diff = longer->size() - shorter->size();
	*shorter = reverse(*shorter);
	while(diff != 0)
	{
		shorter->push_back('0');
		diff--;
	}
	*shorter = reverse(*shorter);
}

std::string addition(std::string n1, std::string n2, int extra, std::string revstring)
{
	int to_take = 0;
	if (n1.size() != 0 && n2.size() != 0) 
	{
		int temp = (n2.back() - '0') + (n1.back() - '0') + extra;
		if (temp > 9)
		{
			int rem = temp % 10;
			to_take = temp / 10;
			revstring.push_back(rem + '0');
		}
		else
		{
			revstring.push_back(temp + '0');
		}
		n1.pop_back();
		n2.pop_back();
		revstring = addition(n1, n2, to_take, revstring);
	}
	else if (extra != 0)
		revstring.push_back(extra + '0');
	return (revstring);
}

bigint::bigint() : buf("0")
{

}

bigint::bigint(unsigned int num)
{
	std::stringstream temp;
	temp << num;
	this->setbuf(temp.str());
}

bigint::bigint(const bigint& other)
{
	*this = other;
}

bigint&	bigint::operator=(const bigint& other)
{
	if (this != &other)
	{
		this->setbuf(other.getbuf());
	}
	return (*this);
}

bool bigint::operator==(const bigint& other) const
{
	if (this->getbuf() != other.getbuf())
		return (false);
	return (true);
}

bigint bigint::operator<<(unsigned int i)
{
	bigint result(*this);
	result <<= i;
	return (result);
}

bigint& bigint::operator<<=(unsigned int i)
{
	if (getbuf() == "0")
		return(*this);
	while(i != 0)
	{
		this->getbuf().push_back('0');
		i--;
	}
	return (*this);
}

bigint bigint::operator>>(unsigned int i)
{
	bigint result(*this);
	result >>= i;
	return (*this);
}

bigint& bigint::operator>>=(unsigned int i)
{
	while(i != 0)
	{
		if (getbuf().size() <= 1)
		{
			setbuf("0");
			break;
		}
		this->getbuf().pop_back();
		i--;
	}
	return (*this);
}


bigint::~bigint()
{

}

bigint	bigint::operator+(const bigint& other) const
{
	std::string num1 = this->buf;
	std::string num2 = other.buf;
	if (num1.size() < num2.size())
		equalize_size(&num1, &num2);
	else if (num2.size() < num1.size())
		equalize_size(&num2, &num1);
	std::string result = addition(num1, num2, 0, "");
	result = reverse(result);
	bigint ret;
	ret.setbuf(result);
	return (ret);
}

//setters

void	bigint::setbuf(std::string num)
{
	this->buf = num;
}
//getters
std::string	bigint::getbuf() const
{
	return(buf);
}

std::string& bigint::getbuf()
{
	return(buf);
}

std::ostream& operator<<(std::ostream& stream, const bigint& val )
{
	return (stream << val.getbuf());
}


int main()
{
    const bigint a(42);
    bigint b(21), c, d(1337), e(d);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;

    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "(c += a) = " << (c += a) << std::endl;

    std::cout << "b = " << b << std::endl;
    std::cout << "++b = " << ++b << std::endl;
    std::cout << "b++ = " << b++ << std::endl;

    std::cout << "(b << 10) + 42 = " << ((b << 10) + 42) << std::endl;
    std::cout << "(d <<= 4) = " << (d <<= 4) << std::endl;
    std::cout << "(d >>= 2) = " << (d >>= (const bigint)2) << std::endl;

    std::cout << "a =" << a << std::endl;
    std::cout << "d =" << d << std::endl;

    std::cout << "(d < a) = " << (d < a) << std::endl;
    std::cout << "(d <= a) = " << (d <= a) << std::endl;
    std::cout << "(d > a) = " << (d > a) << std::endl;
    std::cout << "(d >= a) = " << (d >= a) << std::endl;
    std::cout << "(d == a) = " << (d == a) << std::endl;
    std::cout << "(d != a) = " << (d != a) << std::endl;
}
