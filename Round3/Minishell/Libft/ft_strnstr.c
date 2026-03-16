/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:49:08 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/13 13:49:18 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
	{
		return ((char *)big);
	}
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && 
			(i + j) < len && big[i + j] && little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char big[20] = "Hello world im good";
	char little[6] = "world"; 
	char	*result;
	int i = 0;
	result = strnstr(big, little, 13);

		printf("%c", *result);
}*/
