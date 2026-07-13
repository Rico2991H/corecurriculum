/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hor_inter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:07:02 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/13 12:25:54 by fgreiff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

t_point	first_hor_inter(t_player *player, t_point h, float ray_dir)
{
	float	y_incr;

	if (sin(ray_dir) > 0)
		y_incr = floor(player->player_y) - player->player_y;
	else
		y_incr = ceil(player->player_y) - player->player_y;
	h.y = player->player_y + y_incr;
	if (cos(ray_dir) > 0)
		h.x = player->player_x + fabs(y_incr / (sin(ray_dir) / cos(ray_dir)));
	else
		h.x = player->player_x - fabs(y_incr / (sin(ray_dir) / cos(ray_dir)));
	return (h);
}

t_point	hor_inter(float y_step, float ray_dir, t_point h)
{
	h.y += y_step;
	if (cos(ray_dir) > 0)
		h.x += fabs(y_step / (sin(ray_dir) / cos(ray_dir)));
	else
		h.x -= fabs(y_step / (sin(ray_dir) / cos(ray_dir)));
	return (h);
}

t_point	find_wall_hor(float ray_dir, t_game *game, t_point h)
{
	float	y_step;

	if (sin(ray_dir) > 0)
		y_step = -1;
	else
		y_step = 1;
	h = first_hor_inter(game->player, h, ray_dir);
	while (1)
	{
		if (h.x < 0 || h.x >= game->cols || h.y < 0 || h.y >= game->rows)
		{
			h.x = -1;
			h.y = -1;
			return (h);
		}
		if (check_inter(game->map, h, ray_dir, 1))
			break ;
		h = hor_inter(y_step, ray_dir, h);
	}
	return (h);
}
