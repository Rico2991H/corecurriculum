#include "scalarconverter.hpp"

scalarconverter::scalarconverter()
{
}

scalarconverter::scalarconverter(const scalarconverter& other)
{
    *this = other;
}

scalarconverter& scalarconverter::operator=(const scalarconverter& other)
{
    if (this == &other)
    {
        return (*this);
    }
    return (*this);
}
scalarconverter::~scalarconverter()
{
}

void   scalarconverter::convert(std::string val)
{
    if(val.length() == 3 && isalpha(val[1]));
    {
    
    }
    for (int i = 0; i < val.length(); i++)
    {
        if (!isdigit)
        {
            if(val[val.length()] == 'f')
            {

            }
            break;
        }
        if (i == val.length())
            stoi(val);
    }

}