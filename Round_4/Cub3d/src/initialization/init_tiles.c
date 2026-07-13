/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:27:43 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/12 13:29:43 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

static void	set_tile_size(t_game *game)
{
	int	tile_width;
	int	tile_height;

	tile_width = (WIN_W / 5) / game->cols;
	tile_height = (WIN_H / 5) / game->rows;
	if (tile_width < tile_height)
		game->tile_size = tile_width;
	else
		game->tile_size = tile_height;
}

static void	set_offset_xy(t_game *game)
{
	int	map_pixel_w;
	int	map_pixel_h;

	map_pixel_w = game->cols * game->tile_size;
	map_pixel_h = game->rows * game->tile_size;
	game->offset_x = (WIN_W / 5 - map_pixel_w) / 2;
	game->offset_y = (WIN_H / 5 - map_pixel_h) / 2;
}

void	init_tile_size(t_game *game)
{
	set_tile_size(game);
	set_offset_xy(game);
}
