/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 13:58:46 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 15:50:42 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void	render_helper(t_game *game, t_point player_pos)
{
	float	ray_dir;
	int		i;
	t_point	xy_incr;

	ray_dir = normalize(game->rays->p_start 
			+ degree_to_radians(game->rays->hfov));
	i = 0;
	xy_incr.x = 0;
	xy_incr.y = 0;
	while (i < game->rays->tot_steps)
	{
		game->closest_hit = shooting_rays(game, ray_dir);
		if (game->closest_hit.x != -1)
		{
			game->cur_ray_dir = ray_dir;
			draw_game(game, game->closest_hit, xy_incr, 
				xy_incr.x + game->rays->ray_width);
			draw_ray(game, player_pos, game->closest_hit, 0xF0000);
		}
		xy_incr.x += game->rays->ray_width;
		ray_dir -= game->rays->step_size;
		ray_dir = normalize(ray_dir);
		game->rays->cor_angle = ray_dir - game->rays->p_start;
		i++;
	}
}

int	render_loop(void *param)
{
	t_game	*game;
	t_point	player_pos;

	game = (t_game *)param;
	player_pos.x = game->player->player_x;
	player_pos.y = game->player->player_y;
	move_player(game); 
	fill_window(game);
	render_helper(game, player_pos);
	mlx_put_image_to_window(game->win_ptr->mlx, 
		game->win_ptr->win, 
		game->img_ptr->ptr, 0, 0);
	mlx_put_image_to_window(game->win_ptr->mlx, 
		game->win_ptr->win, 
		game->mm_img_ptr->ptr, 0, 0);
	return (0);
}
