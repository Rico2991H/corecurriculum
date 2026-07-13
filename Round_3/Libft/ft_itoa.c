/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:56:14 by dmungunt          #+#    #+#             */
/*   Updated: 2026/01/30 14:21:49 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_neg_str(char *str, int len, int n)
{
	if (n == -2147483648)
	{
		str[len - 1] = '8';
		len--;
		n = (n / 10);
	}
	while (len)
	{
		str[len - 1] = (n % 10) * (-1) + 48;
		n = n / 10;
		len--;
	}
	str[0] = '-';
}

static void	ft_pos_str(char *str, int len, int n)
{
	while (len)
	{
		str[len - 1] = (n % 10) + 48;
		n = n / 10;
		len--;
	}
}

static int	ft_len(int n)
{
	int	count;
	int	i;

	count = 0;
	i = n;
	if (n <= 0)
		count++;
	while (i / 10 || i % 10)
	{
		i = i / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		ft_neg_str(str, len, n);
	}
	else
	{
		ft_pos_str(str, len, n);
	}
	return (str);
}
