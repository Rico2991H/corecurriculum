/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:05:54 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/04 10:14:37 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_connect = mlx_init();
	if (fractal->mlx_connect == NULL)
		exit(1);
	fractal->mlx_window = mlx_new_window(fractal->mlx_connect, 
			WIDTH, HEIGHT, fractal->name);
	if (fractal->mlx_window == NULL)
		exit(1);
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connect, WIDTH, HEIGHT);
	if (!fractal->img.img_ptr)
	{
		mlx_destroy_window(fractal->mlx_connect, fractal->mlx_window);
		exit(1);
	}
	fractal->img.pixels = mlx_get_data_addr(fractal->img.img_ptr, 
			&fractal->img.bitspp, &fractal->img.line_len, &fractal->img.endian);
	if (!fractal->img.pixels)
	{
		mlx_destroy_image(fractal->mlx_connect, fractal->img.img_ptr);
		mlx_destroy_window(fractal->mlx_connect, fractal->mlx_window);
		exit(1);
	}
}
