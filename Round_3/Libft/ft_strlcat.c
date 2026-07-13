/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:54:32 by dmungunt          #+#    #+#             */
/*   Updated: 2025/03/10 14:27:27 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	i = 0;
	j = dest_len;
	if (dest_len < size - 1 && size > 0)
	{
		while (src[i] && dest_len + i < size - 1)
		{
			dest[j] = src[i];
			i++;
			j++;
		}
		dest[j] = 0;
	}
	if (dest_len >= size)
		dest_len = size;
	return (dest_len + src_len);
}
