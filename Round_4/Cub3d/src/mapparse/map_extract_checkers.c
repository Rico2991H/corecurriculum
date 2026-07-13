/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extract_checkers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:56:41 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 15:51:09 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

int	valid_trimline(char *trimline)
{
	int	i;
	int	onlyspace;

	onlyspace = 1;
	i = 0;
	while (trimline[i])
	{
		if (trimline[i] != '\t' && trimline[i] != ' ' 
			&& trimline[i] != '1' && trimline[i] != '0' && trimline[i] != 'E' 
			&& trimline[i] != 'W' && trimline[i] != 'S' && trimline[i] != 'N')
			return (0);
		if (trimline[i] == '1' || trimline[i] == '0' || trimline[i] == 'E' 
			|| trimline[i] == 'W' || trimline[i] == 'S' || trimline[i] == 'N')
			onlyspace = 0;
		i++;
	}
	if (onlyspace)
		return (0);
	return (1);
}

int	mapstart_checker(char *trimline)
{
	int	i;

	i = 0;
	while (trimline[i])
	{
		if (trimline[i] == '1' || trimline[i] == '0' || trimline[i] == 'E' 
			|| trimline[i] == 'W' || trimline[i] == 'S' || trimline[i] == 'N')
			return (1);
		i++;
	}
	return (0);
}

static void	store_nswe(char *tline, t_game *game)
{
	if (!ft_strncmp(tline, "NO ", 3))
	{
		game->text_ptr->n_text = ft_substr(tline, 3, ft_strlen(&tline[3]));
		game->text_ptr->n_tc++;
	}
	if (!ft_strncmp(tline, "EA ", 3))
	{
		game->text_ptr->e_text = ft_substr(tline, 3, ft_strlen(&tline[3]));
		game->text_ptr->e_tc++;
	}
	if (!ft_strncmp(tline, "SO ", 3))
	{
		game->text_ptr->s_text = ft_substr(tline, 3, ft_strlen(&tline[3]));
		game->text_ptr->s_tc++;
	}
	if (!ft_strncmp(tline, "WE ", 3))
	{
		game->text_ptr->w_text = ft_substr(tline, 3, ft_strlen(&tline[3]));
		game->text_ptr->w_tc++;
	}
}

static void	store_cf(char *tline, t_game *game)
{
	if (!ft_strncmp(tline, "C ", 2))
	{
		game->text_ptr->ceiling = ft_substr(tline, 2, ft_strlen(&tline[2]));
		game->text_ptr->c_counter++;
	}
	if (!ft_strncmp(tline, "F ", 2))
	{
		game->text_ptr->floor = ft_substr(tline, 2, ft_strlen(&tline[2]));
		game->text_ptr->f_counter++;
	}
}

int	check_nswecf(char *tline, int i, t_game *game)
{
	if (tline && (!ft_strncmp(tline, "NO ", 3) || !ft_strncmp(tline, "SO ", 3) 
			|| !ft_strncmp(tline, "WE ", 3) 
			|| !ft_strncmp(tline, "EA ", 3)))
	{
		store_nswe(tline, game);
		if (game->text_ptr->w_tc == 2 || game->text_ptr->n_tc == 2 
			|| game->text_ptr->e_tc == 2 || game->text_ptr->s_tc == 2)
		{
			close(game->fd);
			e_handling(MAP, game);
		}
		i++;
	}
	if (tline && (!ft_strncmp(tline, "C ", 2) 
			|| !ft_strncmp(tline, "F ", 2)))
	{
		store_cf(tline, game);
		if (game->text_ptr->f_counter == 2 || game->text_ptr->c_counter == 2)
		{
			close(game->fd);
			e_handling(MAP, game);
		}
		i++;
	}
	return (i);
}
