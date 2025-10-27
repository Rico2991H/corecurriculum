/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:10:41 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/14 11:30:58 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	in_set(char const c, char const *set)
{
	size_t	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (c == set[j])
		{
			return (1);
		}
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	len_s1;
	size_t	i;
	size_t	k;

	len_s1 = ft_strlen((char *)s1);
	i = 0;
	k = 0;
	while (s1[i] != '\0' && in_set(s1[i], set))
		i++;
	while (len_s1 > i && in_set(s1[len_s1 - 1], set))
		len_s1--;
	ptr = (char *)malloc(sizeof(char) * (len_s1 - i + 1));
	if (!ptr)
	{
		return (NULL);
	}
	while (i < len_s1)
	{
		ptr[k] = s1[i];
		k++;
		i++;
	}
	ptr[k] = '\0';
	return (ptr);
}
