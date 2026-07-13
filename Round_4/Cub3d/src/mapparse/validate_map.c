/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:18:42 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 15:51:19 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

// the map must be surrounde by wals. 
// only one player should allowed and there should be at least one player
// a '0' can not be before, after , above or under a space. 
// the map has already been scanned for illegal characters. 

static int	check_neighbours(int row, int col, t_game *game)
{
	if ((row == 0) || game->map[row - 1][col] == ' ' || 
		(game->map[row - 1][col] != '1' && game->map[row - 1][col] != '0' 
		&& game->map[row - 1][col] != 'N' && game->map[row - 1][col] != 'S' 
		&& game->map[row - 1][col] != 'E' && game->map[row - 1][col] != 'W'))
		return (0);
	if (row == game->rows - 1 || game->map[row + 1][col] == ' ' ||
		(game->map[row + 1][col] != '1' && game->map[row + 1][col] != '0' 
		&& game->map[row + 1][col] != 'N' && game->map[row + 1][col] != 'S' 
		&& game->map[row + 1][col] != 'E' && game->map[row + 1][col] != 'W'))
		return (0);
	if (col == 0 || game->map[row][col - 1] == ' ' ||
		(game->map[row][col - 1] != '1' && game->map[row][col - 1] != '0' 
		&& game->map[row][col - 1] != 'N' && game->map[row][col - 1] != 'S' 
		&& game->map[row][col - 1] != 'E' && game->map[row][col - 1] != 'W'))
		return (0);
	if (col == game->cols - 1 || game->map[row][col + 1] == ' ' ||
		(game->map[row][col + 1] != '1' && game->map[row][col + 1] != '0' 
		&& game->map[row][col + 1] != 'N' && game->map[row][col + 1] != 'S' 
		&& game->map[row][col + 1] != 'E' && game->map[row][col + 1] != 'W'))
		return (0);
	return (1);
}

static int	check_character(char tile)
{
	if (tile == 'N' || tile == 'S' || tile == 'W' || tile == 'E')
		return (1);
	else
		return (0);
}

int	check_cell(int i, int j, t_game *game)
{
	if (game->map[i][j] == '1' || game->map[i][j] == ' ' )
		return (0);
	else if (game->map[i][j] == '0' || game->map[i][j] == 'N' 
		|| game->map[i][j] == 'S' || game->map[i][j] == 'W' 
		|| game->map[i][j] == 'E')
	{
		if (check_neighbours(i, j, game))
			return (check_character(game->map[i][j]));
		else
			return (-1);
	}
	else
		return (-1);
}

int	check_col(int i, t_game *game)
{
	int	j;
	int	tmp;
	int	result;

	j = 0;
	result = 0;
	while (j < game->cols)
	{
		tmp = check_cell(i, j, game);
		if (tmp == -1)
			return (-1);
		result += tmp;
		j++;
	}
	return (result);
}

void	validate_map(t_game *game)
{
	int	i;
	int	player_count;
	int	result;

	i = 0;
	player_count = 0;
	if (game->rows == 0)
		e_handling(MAP, game);
	while (i < game->rows)
	{
		result = check_col(i, game);
		if (result == -1)
			e_handling(MAP, game);
		player_count += result;
		i++;
	}
	if (player_count > 1 || player_count <= 0)
		e_handling(MAP, game);
}
