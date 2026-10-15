#include <string>
#include <iostream>

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
	return (revstring);
}

int main() //why are they negative 
{
	std::string num1 = "345670";
	std::string num2 = "17781342";
	if (num1.size() < num2.size())
	{
		equalize_size(&num1, &num2);
		std::cout << "num1 " << num1 << " num2 " << num2 << std::endl;
	}
	else if (num2.size() < num1.size())
		equalize_size(&num2, &num1);
	std::string result = addition(num1, num2, 0, "");
	result = reverse(result);
	std::cout << result;
	return (0);
}