/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:08:10 by dmungunt          #+#    #+#             */
/*   Updated: 2025/05/16 16:44:10 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long int	number;
	int					minus;

	number = 0;
	minus = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = -minus;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0') * minus;
		++str;
	}
	return (number);
}
