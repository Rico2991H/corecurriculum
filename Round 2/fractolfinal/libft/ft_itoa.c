/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:37:41 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/19 13:42:10 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*itoa_intmin(void)
{
	int		i;
	char	*arraymin;
	char	*int_min;

	int_min = "-2147483648";
	i = 0;
	arraymin = malloc(12);
	while (int_min[i])
	{
		arraymin[i] = int_min[i];
		i++;
	}
	arraymin[i] = '\0';
	return (arraymin);
}

static int	n_zero_or_low(int nbr, char *array)
{
	if (nbr < 0)
	{
		nbr = nbr * -1;
		array[0] = '-';
	}
	if (nbr == 0)
	{
		array[0] = '0';
	}
	return (nbr);
}

static int	calc_len(int n)
{
	int	result;
	int	len;

	result = n;
	len = 0;
	if (n <= 0)
		len++;
	while (result != 0)
	{
		result = result / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		int_len;
	char	*array;	

	if (n == -2147483648)
		return (itoa_intmin());
	int_len = calc_len(n);
	array = malloc(sizeof(char) * (int_len + 1));
	if (!array)
		return (NULL);
	array[int_len] = '\0';
	if (n <= 0)
		n = n_zero_or_low(n, array);
	if (n == 0)
		return (array);
	int_len--;
	while (n != 0)
	{
		array[int_len] = n % 10 + '0';
		n = n / 10;
		int_len--;
	}
	return (array); 
}
/*
#include <stdio.h>
int	main(void)
{
	char	*ptr;
	ptr = ft_itoa(0);
	printf("%s",ptr);
	free(ptr);
    return 0;
}*/
