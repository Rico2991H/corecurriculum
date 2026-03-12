/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:46:06 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/24 13:46:07 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc > 1)
	{
		while(argv[i])
		{
			std::string	str1 = "";
			str1.append(argv[i]);
			for (char& x : str1)
				x = toupper(x);

			std:: cout <<str1;
			i++;
		}
		std:: cout << "\n";
	}
	if (argc == 1)
		std:: cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *\n";
}