#ifndef SEARCHABLE_BAG_HPP
#define SEARCHABLE_BAG_HPP

#include "searchable_bag.hpp"

class set
{
	public:
		set();
		set(searchable_bag& obj);
		set(const set& other);
		set& operator=(const set& other);
		void insert(int val);
		void insert(int *val, int size);
		void print() const;
		void clear();
		bool has(int val) const;
		searchable_bag& get_bag() const;
	private:
		searchable_bag& bag_obj;
};

#endif