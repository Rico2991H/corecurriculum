/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 13:20:45 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 15:51:02 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void	open_file(char *mfile, t_game *game)
{
	game->fd = open(mfile, O_RDONLY);
	if (game->fd < 0)
		e_handling(FD, game);
}

int	check_direction(char *tline)
{
	if (!ft_strncmp(tline, "NO ", 3) 
		|| !ft_strncmp(tline, "SO ", 3) 
		|| !ft_strncmp(tline, "WE ", 3) 
		|| !ft_strncmp(tline, "EA ", 3)
		|| !ft_strncmp(tline, "C ", 2) 
		|| !ft_strncmp(tline, "F ", 2))
		return (1);
	return (0);
}

void	find_dimensions(char *mfile, t_game *game)
{
	char	*line;
	char	*tline;
	int		i;

	open_file(mfile, game);
	i = 0;
	while (1)
	{
		line = get_next_line(game->fd);
		if (!line)
			break ;
		tline = ft_strtrim(line, "\n");
		if (tline && check_direction(tline))
			i++;
		else if (i == 6 && ft_strchr(tline, '1'))
		{
			game->rows++;
			if (ft_strlen(tline) > (size_t)game->cols)
				game->cols = ft_strlen(tline);
		}
		free(line);
		free(tline);
	}
	close(game->fd);
}

char	**create_map(t_game *game)
{
	int		i;
	char	**map;

	i = 0;
	map = malloc((game->rows + 1) * sizeof(char *));
	if (!map)
		e_handling(MALLOC, game);
	while (i < game->rows)
	{
		map[i] = malloc((game->cols + 1) * sizeof(char));
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			e_handling(MALLOC, game);
		}
		i++;
	}
	return (map);
}
