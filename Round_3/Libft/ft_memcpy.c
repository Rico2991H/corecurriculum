/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:53:10 by dmungunt          #+#    #+#             */
/*   Updated: 2025/05/16 15:55:15 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr_d;

	ptr_d = (unsigned char *)dest;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n)
	{
		*(ptr_d++) = *((unsigned char *)src++);
		n--;
	}
	return (dest);
}
