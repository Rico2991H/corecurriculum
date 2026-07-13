/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expansion_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:38:17 by rhoogend          #+#    #+#             */
/*   Updated: 2026/01/30 14:34:33 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_before(char *arg, int i, t_files *files)
{
	int	j;
	int	len;

	len = ft_strlen(files->filename);
	j = 0;
	if (i == 0)
		return (1);
	i--;
	if (arg[i] == files->filename[i])
	{
		while (i >= 0 && len >= 0 && arg[i] == files->filename[i])
		{
			if (arg[i] != files->filename[i])
				return (0);
			i--;
			len--;
		}
		return (1);
	}
	return (0);
}

int	check_after(char *arg, int i, t_files *files, int j)
{
	while (arg[i] && arg[i] == '*')
	{
		i++;
		if (!arg[i])
			return (1);
	}
	while (files->filename[j])
	{
		if (arg[i] == files->filename[j])
		{
			while (arg[i] && files->filename[j])
			{
				i++;
				j++;
				if (arg[i] == '*')
					return (check_after(arg, i, files, j));
				if (arg[i] != files->filename[j])
					return (0);
			}
			return (1);
		}
		j++;
	}
	return (0);
}
