/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 13:10:22 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/26 10:54:52 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

int	ft_atoi_rgb(const char *str)
{
	int	number;

	number = 0;
	while (*str >= '0' && *str <= '9')
	{
		number = number * 10 + (*str - '0');
		if (number > 255)
			return (-1);
		++str;
	}
	return (number);
}
