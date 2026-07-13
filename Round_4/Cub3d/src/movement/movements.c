/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:36:23 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/27 15:51:27 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	play_game(t_game *game)
{
	mlx_hook(game->win_ptr->win, 2, 1, handle_keypress, game);
	mlx_hook(game->win_ptr->win, 3, 2, handle_keyrelease, game);
	mlx_hook(game->win_ptr->win, 17, 0, handle_destroy, game);
}

int	handle_destroy(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	clean_up(game);
	exit (0);
	return (0);
}

int	handle_keypress(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == 65307)
	{
		clean_up(game);
		exit (0);
	}
	else if (keycode == 119)
		game->player->key_w = 1;
	else if (keycode == 97)
		game->player->key_a = 1;
	else if (keycode == 115)
		game->player->key_s = 1;
	else if (keycode == 100)
		game->player->key_d = 1;
	else if (keycode == 65361)
		game->player->key_left = 1;
	else if (keycode == 65363)
		game->player->key_right = 1;
	return (0);
}

int	handle_keyrelease(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == 119)
		game->player->key_w = 0;
	else if (keycode == 97)
		game->player->key_a = 0;
	else if (keycode == 115)
		game->player->key_s = 0;
	else if (keycode == 100)
		game->player->key_d = 0;
	else if (keycode == 65361)
		game->player->key_left = 0;
	else if (keycode == 65363)
		game->player->key_right = 0;
	return (0);
}
