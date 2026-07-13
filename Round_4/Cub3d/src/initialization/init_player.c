/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:06:08 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/11 14:36:28 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static void	find_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'W' || game->map[i][j] == 'E')
			{
				game->player->spawn_dir = game->map[i][j];
				game->player->player_x = (j + 0.5);
				game->player->player_y = (i + 0.5);
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	set_direction(t_game *game)
{
	if (game->player->spawn_dir == 'N')
	{
		game->player->dir_x = 0;
		game->player->dir_y = -1;
	}
	else if (game->player->spawn_dir == 'S')
	{
		game->player->dir_x = 0;
		game->player->dir_y = 1;
	}
	else if (game->player->spawn_dir == 'E')
	{
		game->player->dir_x = 1;
		game->player->dir_y = 0;
	}
	else
	{
		game->player->dir_x = -1;
		game->player->dir_y = 0;
	}
	return ;
}

static void	set_plane(t_game *game)
{
	if (game->player->spawn_dir == 'N')
	{
		game->player->plane_x = 0.66;
		game->player->plane_y = 0;
	}
	else if (game->player->spawn_dir == 'S')
	{
		game->player->plane_x = -0.66;
		game->player->plane_y = 0;
	}
	else if (game->player->spawn_dir == 'E')
	{
		game->player->plane_x = 0;
		game->player->plane_y = 0.66;
	}
	else
	{
		game->player->plane_x = 0;
		game->player->plane_y = -0.66;
	}
	return ;
}

void	init_player(t_game *game)
{
	find_player(game);
	set_direction(game);
	set_plane(game);
	return ;
}
