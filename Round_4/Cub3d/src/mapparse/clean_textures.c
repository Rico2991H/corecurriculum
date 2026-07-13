/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:16:35 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 14:27:20 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

static char	*clean_textures(char *texture)
{
	int		i;
	char	*clean_text;

	i = 0;
	while (texture[i] == ' ' || texture[i] == '\t')
		i++;
	clean_text = ft_substr(&texture[i], 0, ft_strlen(&texture[i]));
	return (clean_text);
}

void	clean_and_free_text(t_game *game)
{
	char	*temp;

	temp = clean_textures(game->text_ptr->n_text);
	free(game->text_ptr->n_text);
	game->text_ptr->n_text = temp;
	temp = clean_textures(game->text_ptr->e_text);
	free(game->text_ptr->e_text);
	game->text_ptr->e_text = temp;
	temp = clean_textures(game->text_ptr->s_text);
	free(game->text_ptr->s_text);
	game->text_ptr->s_text = temp;
	temp = clean_textures(game->text_ptr->w_text);
	free(game->text_ptr->w_text);
	game->text_ptr->w_text = temp;
}
