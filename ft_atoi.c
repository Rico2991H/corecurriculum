/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 15:38:32 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/13 15:38:35 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	minus_checker(int *i, const char *nptr)
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

int	atoi(const char *nptr)
{
	int	number;
	int	i;
	int	pm_counter;
	int	sign;

	i = 0;
	number = 0;
	pm_counter = 0;
	sign = 1;
	while ((nptr[i] == 32) || (nptr[i] >= 9 && nptr[i] <= 13))
	{
		i++;
	}
	sign = minus_checker(&i, nptr);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + nptr[i] - '0';
		i++;
	}
	number = number * sign;
	return (number);
}
/*
int	main(void)
{
	const char nbr[9] = "-3534535";
	int	result = atoi(nbr);
	printf("%d", result);
}*/	
