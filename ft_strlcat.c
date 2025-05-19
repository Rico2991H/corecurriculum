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
size_t	strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	len_src = ft_strlen(src);
	if (size == 0)
	{
		return (0);
	}
	len_dst = ft_strlen(dst);
	if (len_dst >= size)
	{
		return (len_src + size);
	}
	while (src[i] != '\0' && (len_dst + i) < (size -1))
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	if (len_dst + i < size)
	{
		dst[len_dst + i] = '\0';
	}
	return (len_dst + len_src);
}
