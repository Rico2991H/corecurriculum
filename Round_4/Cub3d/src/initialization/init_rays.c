/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 12:48:15 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 14:24:21 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void	calc_p_dir(t_game *game)
{
	if (game->player->dir_y == -1 && game->player->dir_x == 0)
		game->rays->p_start = M_PI / 2;
	if (game->player->dir_y == 1 && game->player->dir_x == 0)
		game->rays->p_start = 3 * M_PI / 2;
	if (game->player->dir_y == 0 && game->player->dir_x == -1)
		game->rays->p_start = M_PI;
	if (game->player->dir_y == 0 && game->player->dir_x == 1)
		game->rays->p_start = 0;
}

void	init_rays(t_game *game)
{
	float	rad_hfov;

	game->rays->fov = 60;
	game->rays->hfov = game->rays->fov / 2;
	rad_hfov = degree_to_radians(game->rays->hfov);
	game->rays->ray_angle = game->rays->hfov;
	game->rays->precision = 0.2;
	game->rays->step_size = degree_to_radians(game->rays->precision);
	game->rays->dist = degree_to_radians(game->rays->fov);
	game->rays->cor_angle = degree_to_radians(game->rays->hfov);
	game->rays->tot_steps = (int)((game->rays->dist / game->rays->step_size));
	game->rays->ray_width = (float)WIN_W / game->rays->tot_steps;
	game->rays->proj_plane = (WIN_W / 2) / tan(rad_hfov);
	calc_p_dir(game);
}
