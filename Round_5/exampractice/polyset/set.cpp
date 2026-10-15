#include "set.hpp"

//set::set() : bag_obj()
//{
//}

set::set(searchable_bag& obj) : bag_obj(obj)
{

}

set::set(const set& other) : bag_obj(other.bag_obj)
{
	*this = other;
}

set& set::operator=(const set& other)
{
	(void) other;
	return *this;
}

bool set::has(int val) const
{
	return (bag_obj.has(val));
}

void set::insert(int val)
{
	if (!has( val))
		get_bag().insert(val);	
}
void set::insert(int *val, int size)
{
	for (int i = 0 ; i < size ; i++)
	{
		insert(val[i]);
	}
}

void set::print() const
{
	get_bag().print();
}

void set::clear()
{
	get_bag().clear();
}
searchable_bag& set::get_bag() const
{
	return (bag_obj);
}
