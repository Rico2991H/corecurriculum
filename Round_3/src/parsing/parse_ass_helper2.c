/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ass_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:14:16 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/11 20:23:16 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

int	find_equals(char *str)
{
	if (!ft_strnstr(str, "=", ft_strlen(str)))
		return (0);
	return (1);
}

void	free_clean(char **buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		free(buf[i]);
		i++;
	}
	free(buf);
}
