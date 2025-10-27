/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:56:30 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/14 10:41:29 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ptr;
	size_t	i;
	size_t	j;

	j = ft_strlen((char *)s1);
	i = 0;
	len = j + ft_strlen((char *)s2);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < j)
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (j != len)
	{
		ptr[j] = s2[i];
		j++;
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}
/*#include <stdio.h>
int	main()
{
	char	str[] = "Hello world how are you?";
	void	*result = ft_strjoin("Hello world", "how are you?");
	char	*casted = (char *)result;
	printf("%s", casted);
}*/
