/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:33:24 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/12 16:28:29 by fgreiff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	rotate_player(t_game *game, float angle)
{
	float	new_dirx;
	float	new_diry;
	float	new_plane_x;
	float	new_plane_y;

	game->rays->p_start = normalize(game->rays->p_start + angle);
	new_dirx = game->player->dir_x * cos(angle)
		+ game->player->dir_y * sin(angle);
	new_diry = -game->player->dir_x * sin(angle)
		+ game->player->dir_y * cos(angle);
	new_plane_x = game->player->plane_x * cos(angle)
		+ game->player->plane_y * sin(angle);
	new_plane_y = -game->player->plane_x * sin(angle)
		+ game->player->plane_y * cos(angle);
	game->player->dir_x = new_dirx;
	game->player->dir_y = new_diry;
	game->player->plane_x = new_plane_x;
	game->player->plane_y = new_plane_y;
}
