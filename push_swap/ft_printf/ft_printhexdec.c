/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexdec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:02:05 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/26 14:02:06 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "libft.h"

static char	*alloc_array(int *i, unsigned int *temp )
{
	char	*array;

	while (*temp != 0)
	{
		*temp = *temp / 16;
		(*i)++;
	}
	array = malloc(sizeof(char) * (*i + 1));
	if (!array)
		return (0);
	array[*i] = '\0';
	return (array);
}

static void	assign_bigx(int temp, char *array, int *i)
{
	if (temp < 10)
		array[*i - 1] = temp + '0';
	if (temp >= 10)
		array[*i - 1] = temp + '7';
	(*i)--;
}

static void	assign_smallx(unsigned int temp, char *array, int *i)
{
	if (temp < 10)
		array[*i - 1] = temp + '0';
	if (temp >= 10)
		array[*i - 1] = temp + '7' + 32;
	(*i)--;
}

static char	*check_x(const char *form, unsigned int *nbr, char *array, int *i)
{
	int	temp;

	while (*nbr > 0)
	{
		temp = *nbr % 16;
		if (*form == 'X')
			assign_bigx(temp, array, i);
		else
			assign_smallx(temp, array, i);
		*nbr = *nbr / 16;
	}
	return (array);
}

int	ft_printhexdec(unsigned int nbr, const char *format)
{
	unsigned int	temp;
	char			*array;
	char			*start;
	int				i;
	int				counter;

	temp = nbr;
	i = 0;
	counter = 0;
	if (nbr == 0)
		return (ft_putchar_fd('0', 1), 1);
	array = alloc_array(&i, &temp);
	array = check_x(format, &nbr, array, &i);
	start = array;
	while (*array)
	{
		ft_putchar_fd(*array, 1);
		array++;
		counter++;
	}
	free(start);
	return (counter);
}
