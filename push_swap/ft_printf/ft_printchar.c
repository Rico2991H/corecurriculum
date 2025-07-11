/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 13:58:15 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/28 14:00:37 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "ft_printf.h"

int	ft_printchar(char c)
{
	int	counter;

	counter = 0;
	ft_putchar_fd(c, 1);
	counter++;
	return (counter);
}
