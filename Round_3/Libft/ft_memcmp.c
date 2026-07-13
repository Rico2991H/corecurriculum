/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:35:54 by dmungunt          #+#    #+#             */
/*   Updated: 2025/05/12 16:58:49 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i != n)
	{
		if (((unsigned char *)s1)[i] < ((unsigned char *)s2)[i])
			return (-1);
		if (((unsigned char *)s1)[i] > ((unsigned char *)s2)[i])
			return (1);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>

int	main(void)
{
	printf ("%d", ft_memcmp("dbcd", "abcf", 4));
	return (0);
}*/
