/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:30:09 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/27 14:39:40 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

// still need check fr max 3 
// need to reject empty values

int	split_is_only_digit(char	*split_rgb)
{
	int	i;

	i = 0;
	if (!split_rgb || split_rgb[0] == '\0')
		return (0);
	while (split_rgb[i])
	{
		if (!ft_isdigit(split_rgb[i]))
			return (0);
		i++;
	}
	return (1);
}

int	trim_rgb(char *rgb, t_game *game)
{
	char	*temp_rgb;
	int		clean_rgb;

	clean_rgb = 0;
	temp_rgb = ft_strtrim(rgb, "  \t");
	if (split_is_only_digit(temp_rgb))
		clean_rgb = ft_atoi_rgb(temp_rgb);
	else
	{
		free(temp_rgb);
		e_handling(RGB, game);
	}
	if (clean_rgb == -1)
	{
		free(temp_rgb);
		return (-1);
	}
	free(temp_rgb);
	return (clean_rgb);
}

int	check_rgb(char *rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (!ft_isdigit(rgb[i]) && rgb[i] != ',' 
			&& rgb[i] != '\t' && rgb[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	split_val_is_3(char **split_rgb, t_game *game)
{
	int	i;

	i = 0;
	while (split_rgb[i])
		i++;
	if (i != 3)
	{
		while (i != 0)
		{
			free(split_rgb[i]);
			i--;
		}
		free(split_rgb[i]);
		free(split_rgb);
		e_handling(RGB, game);
	}
	i = 0; 
	return (1);
}

void	conv_int_rgb(t_game *game, t_rgb *rgb_ptr, char *rgb)
{
	char	**split_rgb;
	int		i;

	i = 0;
	if (check_rgb(rgb))
	{
		split_rgb = ft_split(rgb, ',');
		if (split_val_is_3(split_rgb, game))
		{
			rgb_ptr->r_val = trim_rgb(split_rgb[0], game);
			rgb_ptr->g_val = trim_rgb(split_rgb[1], game);
			rgb_ptr->b_val = trim_rgb(split_rgb[2], game);
		}
		else
			exit(1);
		while (i < 3)
			free(split_rgb[i++]);
		free(split_rgb);
	}
	else
		e_handling(RGB, game);
	if (rgb_ptr->r_val == -1 || rgb_ptr->g_val == -1 
		|| rgb_ptr->b_val == -1)
		e_handling(RGB, game);
}
