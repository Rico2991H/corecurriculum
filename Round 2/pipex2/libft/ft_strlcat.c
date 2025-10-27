/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:03:28 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/12 18:03:31 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	len_src = ft_strlen((char *)src);
	len_dst = ft_strlen(dst);
	if (len_dst < size - 1 && size > 0)
	{
		while (src[i] != '\0' && (len_dst + i) < (size -1))
		{
			dst[len_dst + i] = src[i];
			i++;
		}
		dst[len_dst + i] = 0;
	}
	if (len_dst >= size)
		len_dst = size;
	return (len_dst + len_src);
}
/*#include <stdio.h>
int	main()
{
	char dst[50] = "Hello world";  // Writable buffer
	const char *src = " how are you?";
	size_t size = sizeof(dst);
	size_t	result = ft_strlcat(dst,src, 50);
	size_t	casted = (size_t )result;
	printf("Resulting string: %s\n", dst);
	printf("%zu", casted);
}*/
