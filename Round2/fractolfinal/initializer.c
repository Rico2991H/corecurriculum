/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:05:54 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/11 15:39:49 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fractal_init_struct(t_fractal *f)
{
	int	i;

	i = 0;
	f->name = NULL;
	f->mlx_connect = NULL;
	f->mlx_window = NULL;
	f->max_iterations = 0;
	f->center_r = 0.0;
	f->center_i = 0.0;
	f->zoom = 1.0;
	f->tolerance = 0.0;
	f->c.real = 0.0;
	f->c.imag = 0.0;
	f->z.real = 0.0;
	f->z.imag = 0.0;
	while (i < 3)
	{
		f->roots[i].real = 0.0;
		f->roots[i].imag = 0.0;
		i++;
	}
	f->color.r = 0;
	f->color.g = 0;
	f->color.b = 0;
}

static void	get_adress(t_fractal *fractal)
{
	fractal->img.pixels = mlx_get_data_addr(fractal->img.img_ptr, 
			&fractal->img.bitspp, &fractal->img.line_len, &fractal->img.endian);
	if (!fractal->img.pixels)
	{
		mlx_destroy_image(fractal->mlx_connect, fractal->img.img_ptr);
		mlx_destroy_window(fractal->mlx_connect, fractal->mlx_window);
		mlx_destroy_display(fractal->mlx_connect);
		free (fractal->mlx_connect);
		exit(1);
	}
}

void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_connect = mlx_init();
	if (fractal->mlx_connect == NULL)
		exit(1);
	fractal->mlx_window = mlx_new_window(fractal->mlx_connect, 
			WIDTH, HEIGHT, fractal->name);
	if (fractal->mlx_window == NULL)
	{
		mlx_destroy_display(fractal->mlx_connect);
		free (fractal->mlx_connect);
		exit(1);
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connect, WIDTH, HEIGHT);
	if (!fractal->img.img_ptr)
	{
		mlx_destroy_window(fractal->mlx_connect, fractal->mlx_window);
		mlx_destroy_display(fractal->mlx_connect);
		free (fractal->mlx_connect);
		exit(1);
	}
	get_adress(fractal);
}
