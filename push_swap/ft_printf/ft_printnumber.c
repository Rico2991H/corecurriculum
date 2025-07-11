/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:01:49 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/26 14:01:51 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "libft.h"

int	ft_printnumber(int nbr)
{
	int		counter;
	char	*str;
	char	*start;

	counter = 0;
	str = ft_itoa(nbr);
	start = str;
	while (*str)
	{
		ft_putchar_fd(*str, 1);
		counter++;
		str++;
	}
	free(start);
	return (counter);
}
