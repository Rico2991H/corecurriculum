/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:50:16 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/11 12:19:20 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	resize_scale(double orig_nbr, double max_pixel, 
		double new_min, double new_max)
{
	return ((orig_nbr / max_pixel) * (new_max - new_min) + (new_min));
}

void	ft_mlx_pixel_put(t_img	*data, int x, int y, int color)
{
	char	*dest;

	dest = data->pixels + (y * data->line_len + x * (data->bitspp / 8));
	*(unsigned int *)dest = color;
}

double	assign_color(int i, t_fractal *fractal)
{
	t_rgb	color;
	double	t; 
	int		packed_color;

	t = (double)i / fractal->max_iterations;
	if (i <= 0.5 * fractal->max_iterations)
	{
		color.r = (int)(9 * (1 - t) / fractal->zoom * t * t * t * 255);
		color.g = (int)(35 * (1 - t) * (1 - t) / fractal->zoom * t * t * 255);
		color.b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) 
				/ fractal->zoom * t * 255);
	}
	if (i > 0.5 * fractal->max_iterations)
	{
		color.r = 255 - ((int)(9 * (1 - t) 
					/ fractal->zoom * t * t * t * 255));
		color.g = 255 - ((int)(35 * (1 - t) * (1 - t) 
					/ fractal->zoom * t * t * 255));
		color.b = 255 - ((int)(8.5 * (1 - t) * (1 - t) * (1 - t) 
					/ fractal->zoom * t * 255));
	}
	packed_color = (color.r << 16) | (color.g << 8) | color.b;
	return (packed_color);
}
