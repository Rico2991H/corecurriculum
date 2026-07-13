/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:19:33 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 15:52:07 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void	calloc_game(t_game *game)
{
	game->text_ptr = calloc(1, sizeof(t_texture));
	game->c_rgb = calloc(1, sizeof(t_rgb));
	game->f_rgb = calloc(1, sizeof(t_rgb));
	game->win_ptr = calloc(1, sizeof(t_win));
	game->img_ptr = calloc(1, sizeof(t_img));
	game->mm_img_ptr = calloc(1, sizeof(t_img));
	game->rays = calloc(1, sizeof(t_ray));
	game->textures = calloc(1, sizeof(t_textures));
	game->player = calloc(1, sizeof(t_player));
	calloc_checker(game);
}

static void	init_empty_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->fd = -1;
}

static int	valid_cub_extension(char *file)
{
	int	len;

	if (!file)
		return (0);
	len = ft_strlen(file);
	if (len < 5)
		return (0);
	if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

t_game	init_game(void)
{
	t_game	game;

	game.fd = -1;
	game.cols = 0;
	game.rows = 0;
	game.map = NULL;
	game.offset_x = 0;
	game.offset_y = 0;
	game.text_ptr = NULL;
	game.c_rgb = NULL;
	game.f_rgb = NULL;
	game.win_ptr = NULL;
	game.img_ptr = NULL;
	game.mm_img_ptr = NULL;
	game.rays = NULL;
	game.textures = NULL;
	game.player = NULL;
	game.cur_ray_dir = 0;
	init_empty_game(&game);
	calloc_game(&game);
	return (game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_empty_game(&game);
	if (argc != 2)
		e_handling(ARGS, &game);
	if (!valid_cub_extension(argv[1]))
		e_handling(EXTENSION, &game);
	game = init_game();
	read_map(argv[1], &game);
	clean_and_free_text(&game);
	conv_int_rgb(&game, game.c_rgb, game.text_ptr->ceiling);
	conv_int_rgb(&game, game.f_rgb, game.text_ptr->floor);
	validate_textures(&game);
	validate_map(&game);
	init_player(&game);
	init_rays(&game);
	init_images(&game);
	return (0);
}
