/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:37:02 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/13 13:48:06 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (0);
}
/*#include <stdio.h>
int main()
{
	int i = 0;
	i = ft_memcmp("hello","hellp", 5);
	printf("%d\n", i);
	i = ft_memcmp("hello","hello", 5);
	printf("%d\n", i);
	i = ft_memcmp("hello","hel are your", 8);
	printf("%d\n", i);
}*/
