/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:02:05 by dmungunt          #+#    #+#             */
/*   Updated: 2025/11/15 14:41:20 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_char_cmp(const char c1, const char c2)
{
	if ((unsigned char)c1 != (unsigned char)c2)
		return ((unsigned char)c1 - (unsigned char)c2);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] && str2[i] && i < n)
	{
		if (ft_char_cmp(str1[i], str2[i]))
			return (str1[i] - str2[i]);
		i++;
	}
	if (i < n)
		return (ft_char_cmp(str1[i], str2[i]));
	return (0);
}
