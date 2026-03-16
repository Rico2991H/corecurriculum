/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:20:05 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/12 15:23:09 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "push_swap.h"

static int	minus_checker(int *i, const char *nptr)
{
	int	sign;

	sign = 1;
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
		{
			sign = -1;
			(*i)++;
			return (sign);
		}
		(*i)++;
	}
	return (sign);
}

int	ft_atoi(const char *nptr, int argc, char **argv)
{
	long	number;
	int		i;
	int		sign;

	i = 0;
	number = 0;
	sign = 1;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	sign = minus_checker(&i, nptr);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - '0') * sign;
		i++;
		if (number < -2147483648 || number > 2147483647)
		{
			if (argc == 2)
				free_split(argv);
			write (1, "Error\n", 6);
			exit(1);
		}
	}
	return ((int)number);
}

int	int_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < argc)
	{
		if (argv[i][0] == 45 && argv[i][1] != '\0')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
			{
				write (1, "Error\n", 6);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	doublenum_check(int argcount, int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (i < argcount)
	{
		j = i + 1;
		while (j < argcount)
		{
			if (ft_atoi(argv[i], argc, argv) == ft_atoi(argv[j], argc, argv))
			{
				write (1, "Error\n", 6);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
