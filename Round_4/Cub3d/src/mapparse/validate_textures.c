/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 15:19:57 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/27 15:54:56 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static int	path_is_xpm(char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (0);
	return (1);
}

static void	check_texture_path(t_game *game, char *path)
{
	int	fd;

	if (!path_is_xpm(path))
		e_handling(TEXTURE, game);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		e_handling(TEXTURE, game);
	close(fd);
}

void	validate_textures(t_game *game)
{
	check_texture_path(game, game->text_ptr->n_text);
	check_texture_path(game, game->text_ptr->s_text);
	check_texture_path(game, game->text_ptr->e_text);
	check_texture_path(game, game->text_ptr->w_text);
}
