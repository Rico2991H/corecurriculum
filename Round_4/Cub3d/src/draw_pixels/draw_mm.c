/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 13:26:13 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/26 09:57:50 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

static void	draw_tile(t_game *game, int start_x, int start_y, int color)
{
	int		x;
	int		y;
	t_img	*img;

	img = game->mm_img_ptr;
	x = start_x;
	y = start_y;
	while (x < start_x + game->tile_size)
	{
		while (y < start_y + game->tile_size)
		{
			my_mlx_pixel_put(img, x, y, color);
			y++;
		}
		x++;
		y = start_y;
	}
}

void	draw_ray(t_game *game, t_point start, t_point end, int color)
{
	float	x_inc;
	float	y_inc;
	float	steps;
	int		i;

	steps = fmax(fabs(end.x - start.x), fabs(end.x - start.y)) * 100;
	x_inc = (end.x - start.x) / steps;
	y_inc = (end.y - start.y) / steps;
	i = 0;
	while (i < (int)steps)
	{
		my_mlx_pixel_put(
			game->mm_img_ptr,
			game->offset_x + (int)(start.x * game->tile_size),
			game->offset_y + (int)(start.y * game->tile_size),
			color
			);
		start.x += x_inc;
		start.y += y_inc;
		i++;
	}
}

void	set_color(int *color, int c_count, int r_count, t_game *game)
{
	if ((game->map[r_count][c_count]) == '0' 
		|| (game->map[r_count][c_count]) == 'N'
		|| (game->map[r_count][c_count]) == 'E' 
		|| (game->map[r_count][c_count]) == 'S'
		|| (game->map[r_count][c_count]) == 'W')
		*color = 0xFF69B4;
	if ((game->map[r_count][c_count]) == '1')
		*color = 0x00FF00;
	if ((game->map[r_count][c_count]) == ' ')
		*color = 0x00FFFF;
}

void	fill_window(t_game *game)
{
	int	c_count;
	int	r_count;
	int	start_x;
	int	start_y;
	int	color;

	start_x = 0;
	start_y = 0;
	r_count = 0;
	color = 0;
	while (r_count < game->rows)
	{
		c_count = 0;
		while (c_count < game->cols)
		{
			set_color(&color, c_count, r_count, game);
			start_y = game->offset_y + r_count * game->tile_size;
			start_x = game->offset_x + c_count * game->tile_size;
			draw_tile(game, start_x, start_y, color);
			c_count++;
		}
		r_count++;
	}
}
