/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fprim2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:33:16 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/20 14:33:18 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	isprime(int nb)
{
	int i = 2;
	
	while (i * i <= nb)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

void	fprime(int nb)
{
	int i = 2;
	
	while (nb != 1)
	{
		if (isprime(i) && nb % i == 0)
		{
			printf("%d", i);
			nb = nb / i;
			if (nb == 1)
				break;
			printf("*");
		}
		else
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc == 2)
		fprime(atoi(argv[1]));
}
