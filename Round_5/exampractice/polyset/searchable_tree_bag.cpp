#include "searchable_tree_bag.hpp"

searchable_tree_bag::searchable_tree_bag()
{

}

searchable_tree_bag::searchable_tree_bag(const searchable_tree_bag& other) : tree_bag(other) , searchable_bag(other)
{

}

searchable_tree_bag& searchable_tree_bag::operator=(const searchable_tree_bag& other)
{
	if (this != &other)
	{
		tree_bag::operator=(other);
		searchable_bag::operator=(other);
	}
	return (*this);
}

searchable_tree_bag::~searchable_tree_bag()
{

}

bool searchable_tree_bag::has(int val) const
{
	node *temp = this->tree;
	while (temp)
	{
		if (temp->value == val)
			return (true);
		if (temp->value < val)
			temp = temp->r;
		if (temp->value > val)
			temp = temp->l;
	}
	return false;
}
