/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:46:06 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/02 15:05:19 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include <string>

int	main(int argc, char **argv)
{
	int	i;
	std::string	str1 = "";
	i = 1;
	if (argc > 1)
	{
		while (argv[i])
		{
			str1.append(argv[i]);
			str1.append(" ");
			i++;
		}
		int len = str1.length();
		if (!str1.empty())
			str1.resize(len - 1);
		for (int i = 0 ; i < len - 1 ; i++)
			str1[i] = toupper(str1[i]);
		std:: cout << str1 << "\n";
	}
	if (argc == 1)
		std:: cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
}