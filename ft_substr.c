/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:39:22 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/14 09:55:53 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (!ptr)
		return (NULL);
	while (i != len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	return (ptr);
}
