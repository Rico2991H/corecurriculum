/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:59:11 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/27 09:04:06 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "libft.h"

static char	*alloc_array(int *counter, unsigned long long temp )
{
	char	*array;

	while (temp > 0)
	{
		temp = temp / 16;
		(*counter)++;
	}
	array = malloc(sizeof(char) * (*counter + 1));
	if (!array)
		return (NULL);
	array[*counter] = '\0';
	return (array);
}

static void	assign(char *array, int counter, unsigned long long unbr)
{
	int	temp;

	while (unbr > 0)
	{
		temp = (unbr % 16);
		if (temp < 10)
			array[counter - 1] = temp + '0';
		if (temp >= 10)
			array[counter - 1] = temp + '7' + 32;
		counter--;
		unbr = unbr / 16;
	}
}

int	ft_printptr(void *ptr)
{
	int					counter;
	int					i;
	unsigned long long	unbr;
	char				*array;

	unbr = (unsigned long long)ptr;
	counter = 0;
	i = 0;
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	array = alloc_array(&counter, unbr);
	assign(array, counter, unbr);
	ft_putstr_fd ("0x", 1);
	while (array[i] != '\0')
	{
		ft_putchar_fd(array[i], 1);
		i++;
	}
	free(array);
	return (counter + 2);
}
