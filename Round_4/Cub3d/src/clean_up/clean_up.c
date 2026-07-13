/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 16:33:56 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/27 15:49:33 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static void	map_free(char **str, int rows)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (i < rows)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_text_ptr(t_texture *text_ptr)
{
	if (!text_ptr)
		return ;
	free(text_ptr->ceiling);
	free(text_ptr->e_text);
	free(text_ptr->floor);
	free(text_ptr->n_text);
	free(text_ptr->s_text);
	free(text_ptr->w_text);
	free(text_ptr);
}

static void	free_mlx(t_win *win_ptr, t_img *img_ptr, t_img *mm_img_ptr)
{
	if (!win_ptr || !win_ptr->mlx)
		return ;
	if (img_ptr)
		mlx_destroy_image(win_ptr->mlx, img_ptr->ptr);
	if (mm_img_ptr)
		mlx_destroy_image(win_ptr->mlx, mm_img_ptr->ptr);
	if (win_ptr->win)
		mlx_destroy_window(win_ptr->mlx, win_ptr->win);
	if (win_ptr->mlx)
	{
		mlx_destroy_display(win_ptr->mlx);
		free(win_ptr->mlx);
	}
}

void	clean_up(t_game *game)
{
	if (!game)
		return ;
	map_free(game->map, game->rows);
	free_text_ptr(game->text_ptr);
	destroy_textures(game);
	free_mlx(game->win_ptr, game->img_ptr, game->mm_img_ptr);
	if (game->player)
		free(game->player);
	if (game->win_ptr)
		free(game->win_ptr);
	if (game->img_ptr)
		free(game->img_ptr);
	if (game->c_rgb)
		free(game->c_rgb);
	if (game->f_rgb)
		free(game->f_rgb);
	if (game->textures)
		free(game->textures);
	if (game->mm_img_ptr)
		free(game->mm_img_ptr);
	if (game->rays)
		free(game->rays);
}
