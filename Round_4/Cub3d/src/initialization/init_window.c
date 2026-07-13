/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:58:35 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 15:17:33 by fgreiff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > img->width || y > img->height)
		return ;
	img->offset = (y * img->line_len + x * (img->bpp / 8));
	dst = img->addr + img->offset;
	*(unsigned int *)dst = color;
}

float	normalize(float n)
{
	if (n > 2 * M_PI)
		n -= 2 * M_PI;
	if (n < 0)
		n += 2 * M_PI;
	return (n);
}

static void	init_game_img(t_game *game)
{
	game->img_ptr->ptr = mlx_new_image(game->win_ptr->mlx, WIN_W, WIN_H);
	game->img_ptr->addr = mlx_get_data_addr(game->img_ptr->ptr, 
			&game->img_ptr->bpp, 
			&game->img_ptr->line_len, 
			&game->img_ptr->endian);
	game->img_ptr->width = WIN_W;
	game->img_ptr->height = WIN_H;
}

static void	init_mm_img(t_game *game)
{
	game->mm_img_ptr->ptr = mlx_new_image(game->win_ptr->mlx, 
			(int)(WIN_W / 5), (int)(WIN_H / 5));
	game->mm_img_ptr->addr = mlx_get_data_addr(game->mm_img_ptr->ptr, 
			&game->mm_img_ptr->bpp, 
			&game->mm_img_ptr->line_len, 
			&game->mm_img_ptr->endian);
	game->mm_img_ptr->width = WIN_W / 5;
	game->mm_img_ptr->height = WIN_H / 5;
}

void	init_images(t_game *game)
{
	game->win_ptr->mlx = mlx_init();
	if (!game->win_ptr->mlx)
		e_handling(MLX, game);
	init_textures(game);
	game->win_ptr->win = mlx_new_window(game->win_ptr->mlx,
			WIN_W, WIN_H, "CUB3D");
	if (!game->win_ptr->win)
		e_handling(MLX, game);
	init_mm_img(game);
	init_game_img(game);
	game->closest_hit.x = 0;
	game->closest_hit.y = 0;
	init_tile_size(game);
	play_game(game);
	mlx_loop_hook(game->win_ptr->mlx, render_loop, game);
	mlx_loop(game->win_ptr->mlx);
}
