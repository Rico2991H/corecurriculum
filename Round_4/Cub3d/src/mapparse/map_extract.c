/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:18:55 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 15:51:13 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

static int	store_map(char *trimline, t_game *game, char **map, int *j)
{
	static int	map_started;
	int			i;

	if (!map_started && mapstart_checker(trimline))
		map_started = 1;
	if (map_started && *j < game->rows)
	{
		if (!valid_trimline(trimline))
			return (-1);
		i = 0;
		while (i < game->cols)
		{
			if (i < (int)ft_strlen(trimline))
				map[*j][i] = trimline[i];
			else
				map[*j][i] = ' ';
			i++;
		}
		map[*j][i] = '\0';
		(*j)++;
	}
	return (0);
}

static void	check_i_close_fd(int i, t_game *game)
{
	if (i != 6)
	{
		close(game->fd);
		e_handling(COLOR, game);
	}
	close(game->fd);
}

static void	drain_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static void	check_store_map(t_game *game, char *line, char *trimline, int *j)
{
	if (store_map(trimline, game, game->map, j) == -1)
	{
		free(line);
		free(trimline);
		drain_gnl(game->fd);
		close(game->fd);
		e_handling(MAP, game);
	}
}

void	read_map(char *mfile, t_game *game)
{
	char	*line;
	int		i;
	int		j;
	char	*trimline;

	i = 0;
	j = 0;
	find_dimensions(mfile, game);
	game->map = create_map(game);
	open_file(mfile, game);
	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			break ;
		trimline = ft_strtrim(line, "\n");
		if (i < 6)
			i = check_nswecf(trimline, i, game);
		else if (i == 6)
			check_store_map(game, line, trimline, &j);
		free(line);
		free(trimline);
	}
	game->map[j] = NULL;
	check_i_close_fd(i, game);
}
