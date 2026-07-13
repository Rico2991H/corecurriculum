/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vert_inter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 12:05:14 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/13 12:28:26 by fgreiff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

t_point	first_vert_inter(t_player *player, t_point v, float ray_dir)
{
	float	x_incr;

	if (cos(ray_dir) > 0)
		x_incr = ceil(player->player_x) - player->player_x;
	else
		x_incr = floor(player->player_x) - player->player_x;
	v.x = player->player_x + x_incr;
	if (sin(ray_dir) > 0)
		v.y = player->player_y - fabs((sin(ray_dir) / cos(ray_dir)) * x_incr);
	else
		v.y = player->player_y + fabs((sin(ray_dir) / cos(ray_dir)) * x_incr);
	return (v);
}

t_point	vert_inter(float x_step, float ray_dir, t_point v)
{
	v.x += x_step;
	if (sin(ray_dir) > 0)
		v.y -= fabs((sin(ray_dir) / cos(ray_dir)) * x_step);
	else
		v.y += fabs((sin(ray_dir) / cos(ray_dir)) * x_step);
	return (v);
}

t_point	find_wall_vert(float ray_dir, t_game *game, t_point v)
{
	float	x_step;

	if (cos(ray_dir) > 0)
		x_step = 1;
	else
		x_step = -1;
	v = first_vert_inter(game->player, v, ray_dir);
	while (1)
	{
		if (v.x < 0 || v.x >= game->cols || v.y < 0 || v.y >= game->rows)
		{
			v.x = -1;
			v.y = -1;
			return (v);
		}
		if (check_inter(game->map, v, ray_dir, 0))
			break ;
		v = vert_inter(x_step, ray_dir, v);
	}
	return (v);
}
