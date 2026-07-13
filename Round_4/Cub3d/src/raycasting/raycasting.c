/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 10:04:49 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/26 12:30:31 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

// degrees = radians * (180 / pi)
// north position is a 270 degreees = 3pi / 2
// east position is at 0 degrees = 3pi/ 2
//south position is at 90 degrees = pi / 2
// west poisiton is at 180 degrees = pi

float	degree_to_radians(float degree)
{
	return (degree * M_PI / 180);
}

int	check_inter(char **map, t_point inter, float ray_dir, int is_ver)
{
	int	x;
	int	y;

	x = (int)inter.x;
	y = (int)inter.y;
	(void)ray_dir;
	if (cos(ray_dir) < 0 && is_ver == 0)
		x -= 1;
	if (sin(ray_dir) > 0 && is_ver == 1)
		y -= 1;
	if (y < 0 || map[y] == NULL)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (1);
	if (map[(int)y][(int)x] == '1')
		return (1);
	else
		return (0);
}

t_point	compare_vh(t_game *game, t_point v, t_point h)
{
	double	v_dist;
	double	h_dist;

	v_dist = (v.x - game->player->player_x) * (v.x - game->player->player_x)
		+ (v.y - game->player->player_y) * (v.y - game->player->player_y);
	h_dist = (h.x - game->player->player_x) * (h.x - game->player->player_x)
		+ (h.y - game->player->player_y) * (h.y - game->player->player_y);
	if (v_dist < h_dist)
	{
		game->hit_vertical = 1;
		return (v);
	}
	game->hit_vertical = 0;
	return (h);
}

t_point	shooting_rays(t_game *game, float ray_dir)
{
	t_point	v;
	t_point	h;
	t_point	error;

	v.y = 0; 
	v.x = 0;
	error.x = 0;
	error.y = 0;
	h.x = 0;
	h.y = 0;
	v = find_wall_vert(ray_dir, game, v);
	h = find_wall_hor(ray_dir, game, h);
	if (v.x == -1 && h.x == -1)
		return (error);
	else if (v.x == -1)
	{
		game->hit_vertical = 0;
		return (h);
	}
	if (h.x == -1)
	{
		game->hit_vertical = 1;
		return (v);
	}
	return (compare_vh(game, v, h));
}
