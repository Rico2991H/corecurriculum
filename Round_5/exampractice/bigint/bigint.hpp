#include <iostream>
#include <string>
#include <sstream>


class bigint
{
	public:
	bigint();
	bigint(unsigned int num);
	bigint(const bigint& other);

	bigint& operator=(const bigint& other);
	bigint	operator+(const bigint& other) const;
	bool operator==(const bigint& other) const;
	bigint operator<<(unsigned int i);
	bigint& operator<<=(unsigned int i);
	bigint& operator>>=(unsigned int i);
	bigint operator>>(unsigned int i);
	~bigint();



	//getters
	std::string 	getbuf() const;
	std::string&	getbuf();
	void			setbuf(std::string num);
	private:
	std::string buf;

};