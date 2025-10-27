/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunsint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:29:21 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/27 13:35:59 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "ft_printf.h"

int	writezero(void)
{
	write(1, "0", 1);
	return (1);
}

int	ft_printunsint(unsigned int nbr)
{
	int		i;
	int		count;	
	char	buffer[11];

	i = 10;
	buffer[i] = '\0';
	i--;
	count = 0;
	if (nbr == 0)
		return (writezero());
	while (nbr > 0)
	{
		buffer[i] = (nbr % 10) + '0';
		nbr = nbr / 10;
		i--;
	}
	i++;
	while (buffer[i])
	{
		write(1, &buffer[i], 1);
		i++;
		count++;
	}
	return (count);
}
