/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_handling.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 13:27:01 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 15:50:01 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void	exit_error(t_game *game, char *msg)
{
	write(2, "Error\n", 6);
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	clean_up(game);
	exit(EXIT_FAILURE);
}

void	e_handling(t_e_error type, t_game *game)
{
	if (type == MALLOC)
		exit_error(game, "memory allocation failed");
	else if (type == COLOR)
		exit_error(game, "missing texture or color identifier");
	else if (type == FD)
		exit_error(game, "could not open map file");
	else if (type == MAP)
		exit_error(game, "invalid map description");
	else if (type == RGB)
		exit_error(game, "invalid RGB color value");
	else if (type == ARGS)
		exit_error(game, "usage: ./cub3D <map.cub>");
	else if (type == EXTENSION)
		exit_error(game, "map file must use .cub extension");
	else if (type == TEXTURE)
		exit_error(game, "failed to load texture");
	else if (type == MLX)
		exit_error(game, "failed to initialize mlx");
}

static void	calloc_e_cleaner(t_game *game)
{
	free(game->text_ptr);
	free(game->c_rgb);
	free(game->f_rgb);
	free(game->win_ptr);
	free(game->img_ptr);
	free(game->mm_img_ptr);
	free(game->rays);
	free(game->textures);
	free(game->player);
	e_handling(MALLOC, game);
}

void	calloc_checker(t_game *game)
{
	if (!game->text_ptr || !game->c_rgb || !game->f_rgb || !game->win_ptr
		|| !game->img_ptr || !game->mm_img_ptr || !game->rays || !game->textures
		|| !game->player)
		calloc_e_cleaner(game);
}
