/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:17:10 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/11 15:33:15 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

static	void	change_color(t_fractal *fractal)
{
	int	temp;

	temp = fractal->color.r;
	fractal->color.r = fractal->color.g;
	fractal->color.g = fractal->color.b;
	fractal->color.b = temp;
}

int	on_use_key(int keysym, t_fractal *fractal)
{
	if (keysym == 0xff1b)
	{
		if (fractal->mlx_connect && fractal->mlx_window)
			mlx_destroy_window(fractal->mlx_connect, fractal->mlx_window);
		if (fractal->mlx_connect)
		{
			mlx_destroy_display(fractal->mlx_connect);
			free(fractal->mlx_connect);
		}
		exit(0);
	}
	if (keysym == 65361)
		fractal->center_r -= 0.05;
	if (keysym == 65364)
		fractal->center_i += 0.05;
	if (keysym == 65363)
		fractal->center_r += 0.05;
	if (keysym == 65362) 
		fractal->center_i -= 0.05;
	if (keysym == 32)
		change_color(fractal);
	fractal_render(fractal);
	mlx_put_image_to_window(fractal->mlx_connect, fractal->mlx_window, 
		fractal->img.img_ptr, 0, 0);
	return (0);
}

int	on_press_x(t_fractal *fractal)
{
	if (fractal->img.img_ptr)
		mlx_destroy_image(fractal->mlx_connect, fractal->img.img_ptr);
	if (fractal->mlx_connect && fractal->mlx_window)
		mlx_destroy_window(fractal->mlx_connect, fractal->mlx_window);
	if (fractal->mlx_connect)
	{
		mlx_destroy_display(fractal->mlx_connect);
		free(fractal->mlx_connect);
	}
	exit(0);
}

int	mouse_zoom(int button, int x, int y, t_fractal *fractal)
{
	double	zoom_rate;
	double	mouse_r;
	double	mouse_i;

	if (button != 4 && button != 5)
		return (0);
	if (button == 4)
		zoom_rate = 0.9;
	if (button == 5)
		zoom_rate = 1.1;
	mouse_r = resize_scale(x, WIDTH, 
			fractal->center_r - fractal->zoom, 
			fractal->center_r + fractal->zoom);
	mouse_i = resize_scale(y, HEIGHT, 
			fractal->center_i - fractal->zoom, 
			fractal->center_i + fractal->zoom);
	fractal->zoom *= zoom_rate;
	fractal->center_r = mouse_r;
	fractal->center_i = mouse_i;
	fractal_render(fractal);
	mlx_put_image_to_window(fractal->mlx_connect, 
		fractal->mlx_window, fractal->img.img_ptr, 0, 0);
	return (0);
}
