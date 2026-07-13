/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 13:48:55 by dmungunt          #+#    #+#             */
/*   Updated: 2025/05/21 10:08:40 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	if (nmemb == 0 || size == 0)
		return (arr = (void *)malloc(0));
	if (2147483647 / nmemb < size)
		return (NULL);
	arr = (void *)malloc(nmemb * size);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, (nmemb * size));
	return (arr);
}
