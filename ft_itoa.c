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

int	calc_len(int n)
{
	int	result;
	int	len;

	result = n;
	len = 0;
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

	int_len = calc_len(n);
	array = malloc(sizeof(char) * (int_len + 1));
	array[int_len] = '\0';
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
int	main(void)
{
	int	i = 0;
	char	*ptr;
	ptr = ft_itoa(45678);
	while (ptr[i] != '\0')
	{
		printf("%c",ptr[i]);
		i++;
	}
}*/
