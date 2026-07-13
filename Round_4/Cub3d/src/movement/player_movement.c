/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgreiff <fgreiff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 11:04:33 by fgreiff           #+#    #+#             */
/*   Updated: 2026/05/26 15:19:04 by fgreiff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static void	move_forward(t_game *game)
{
	float	new_posx;
	float	new_posy;

	new_posx = game->player->player_x + (game->player->dir_x * MOVE_SPEED);
	if (game->map[(int)game->player->player_y][(int)new_posx] != '1')
		game->player->player_x = new_posx;
	new_posy = game->player->player_y + (game->player->dir_y * MOVE_SPEED);
	if (game->map[(int)new_posy][(int)game->player->player_x] != '1')
		game->player->player_y = new_posy;
}

static void	move_back(t_game *game)
{
	float	new_posx;
	float	new_posy;

	new_posx = game->player->player_x - (game->player->dir_x * MOVE_SPEED);
	if (game->map[(int)game->player->player_y][(int)new_posx] != '1')
		game->player->player_x = new_posx;
	new_posy = game->player->player_y - (game->player->dir_y * MOVE_SPEED);
	if (game->map[(int)new_posy][(int)game->player->player_x] != '1')
		game->player->player_y = new_posy;
}

static void	move_left(t_game *game)
{
	float	new_posx;
	float	new_posy;

	new_posx = game->player->player_x - (game->player->plane_x * MOVE_SPEED);
	if (game->map[(int)game->player->player_y][(int)new_posx] != '1')
		game->player->player_x = new_posx;
	new_posy = game->player->player_y - (game->player->plane_y * MOVE_SPEED);
	if (game->map[(int)new_posy][(int)game->player->player_x] != '1')
		game->player->player_y = new_posy;
}

static void	move_right(t_game *game)
{
	float	new_posx;
	float	new_posy;

	new_posx = game->player->player_x + (game->player->plane_x * MOVE_SPEED);
	if (game->map[(int)game->player->player_y][(int)new_posx] != '1')
		game->player->player_x = new_posx;
	new_posy = game->player->player_y + (game->player->plane_y * MOVE_SPEED);
	if (game->map[(int)new_posy][(int)game->player->player_x] != '1')
		game->player->player_y = new_posy;
}

void	move_player(t_game *game)
{
	if (game->player->key_w == 1)
		move_forward(game);
	if (game->player->key_a == 1)
		move_left(game);
	if (game->player->key_s == 1)
		move_back(game);
	if (game->player->key_d == 1)
		move_right(game);
	if (game->player->key_left == 1)
		rotate_player(game, ROT_SPEED);
	if (game->player->key_right == 1)
		rotate_player(game, -ROT_SPEED);
	else
		return ;
}
