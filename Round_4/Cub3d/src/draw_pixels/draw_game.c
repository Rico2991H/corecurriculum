/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 10:23:24 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 15:34:57 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

static t_tex	*pick_texture(t_game *game)
{
	if (game->hit_vertical == 1)
	{
		if (cos(game->cur_ray_dir) > 0)
			return (&game->textures->w);
		return (&game->textures->e);
	}
	if (sin(game->cur_ray_dir) > 0)
		return (&game->textures->s);
	return (&game->textures->n);
}

static int	read_tex_pixel(t_tex *tex, int x, int y)
{
	char	*p;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	p = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)p);
}

void	draw(t_game *game, float start_wall, float end_wall, t_point xy_inc)
{
	int		color;
	int		tex_y;
	float	x;
	float	y;
	t_rgb	*rgb;

	rgb = game->c_rgb;
	x = xy_inc.x;
	y = xy_inc.y;
	x = floor(x);
	if (y < start_wall)
		color = (rgb->r_val << 16) | (rgb->g_val << 8) | rgb->b_val; 
	else if (y < end_wall)
	{
		tex_y = (int)(((y - start_wall) / game->cur_wall_height)
				* game->cur_tex->height);
		color = read_tex_pixel(game->cur_tex, game->cur_tex_x, tex_y);
	}
	else
	{
		rgb = game->f_rgb;
		color = (rgb->r_val << 16) | (rgb->g_val << 8) | rgb->b_val; 
	}
	my_mlx_pixel_put(game->img_ptr, (int)x, (int)y, color);
}

static void	get_tex(t_game *game, float wall_height, t_point end)
{
	game->cur_wall_height = wall_height;
	game->cur_tex = pick_texture(game);
	if (game->hit_vertical == 1)
		game->cur_tex_x = (int)((end.y - floor(end.y)) * game->cur_tex->width);
	else
		game->cur_tex_x = (int)((end.x - floor(end.x)) * game->cur_tex->width);
}

void	draw_game(t_game *game, t_point end,
		t_point xy_incr, float end_x)
{
	t_point	delta;
	float	wall_height;
	float	start_wall;
	float	end_wall;

	delta.x = end.x - game->player->player_x;
	delta.y = end.y - game->player->player_y;
	game->rays->total_d = sqrt(delta.x * delta.x + delta.y * delta.y);
	game->rays->total_d = game->rays->total_d * cos(game->rays->cor_angle);
	wall_height = (1.0 / game->rays->total_d) * game->rays->proj_plane;
	start_wall = (WIN_H / 2) - (wall_height / 2);
	end_wall = start_wall + wall_height;
	get_tex(game, wall_height, end);
	while (xy_incr.x < end_x)
	{
		while (xy_incr.y < WIN_H)
		{
			draw(game, start_wall, end_wall, xy_incr);
			xy_incr.y++;
		}
		xy_incr.y = 0;
		xy_incr.x++;
	}
}
