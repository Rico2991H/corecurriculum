/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:28:42 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/27 15:50:17 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	load_one_text(t_game *game, char *path, t_tex *dst)
{
	dst->ptr = mlx_xpm_file_to_image(game->win_ptr->mlx, path,
			&dst->width, &dst->height);
	if (!dst->ptr)
		return (0);
	dst->addr = mlx_get_data_addr(dst->ptr, &dst->bpp,
			&dst->line_len, &dst->endian);
	return (1);
}

static void	tex_load_failed(t_game *game, char *which)
{
	if (!ft_strncmp(which, "N", 2))
		exit_error(game, "failed to load north texture");
	else if (!ft_strncmp(which, "S", 2))
		exit_error(game, "failed to load south texture");
	else if (!ft_strncmp(which, "E", 2))
		exit_error(game, "failed to load east texture");
	else if (!ft_strncmp(which, "W", 2))
		exit_error(game, "failed to load west texture");
	else
		e_handling(TEXTURE, game);
}

void	init_textures(t_game *game)
{
	if (!load_one_text(game, game->text_ptr->n_text, &game->textures->n))
		tex_load_failed(game, "N");
	if (!load_one_text(game, game->text_ptr->s_text, &game->textures->s))
		tex_load_failed(game, "S");
	if (!load_one_text(game, game->text_ptr->e_text, &game->textures->e))
		tex_load_failed(game, "E");
	if (!load_one_text(game, game->text_ptr->w_text, &game->textures->w))
		tex_load_failed(game, "W");
}

void	destroy_textures(t_game *game)
{
	if (!game->textures)
		return ;
	if (game->win_ptr && game->win_ptr->mlx)
	{
		if (game->textures->n.ptr)
			mlx_destroy_image(game->win_ptr->mlx, game->textures->n.ptr);
		if (game->textures->s.ptr)
			mlx_destroy_image(game->win_ptr->mlx, game->textures->s.ptr);
		if (game->textures->e.ptr)
			mlx_destroy_image(game->win_ptr->mlx, game->textures->e.ptr);
		if (game->textures->w.ptr)
			mlx_destroy_image(game->win_ptr->mlx, game->textures->w.ptr);
	}
	free(game->textures);
	game->textures = NULL;
}
