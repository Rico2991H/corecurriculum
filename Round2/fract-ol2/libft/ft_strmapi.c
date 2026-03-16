/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:32:58 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/19 11:35:33 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)( unsigned int, char))
{
	int			i;
	int			len;
	char		*result;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen((char *)s);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
char	map_index_case(unsigned int i, char c)
{
	if (i % 2 == 0)
		return (char)toupper(c);
	else
		return (char)tolower(c);
}
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int	main(void)
{
	char const *original = "hElLo WoRlD!";
	char *mapped = ft_strmapi(original, map_index_case);

	if (mapped)
	{
		printf("Original: %s\n", original);
		printf("Mapped:   %s\n", mapped);
		free(mapped);  // Don't forget to free the returned string!
	}
	else
	{
		printf("ft_strmapi returned NULL\n");
	}

	return 0;
}*/
