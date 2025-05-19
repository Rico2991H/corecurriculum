/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:12:02 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/13 17:12:04 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "stdlib.h"

char	*strdup(const char *s)
{
	int		i;
	int		len;
	char	*ptr;

	i = 0;
	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
