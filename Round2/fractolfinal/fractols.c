/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractols.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:57:26 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/14 09:59:28 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandlebrot(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	int			i;
	double		clr;
	double		temp_real;
	double		temp_imag;

	i = 0;
	z.real = 0.0;
	z.imag = 0.0;
	fractal->max_iterations = 300;
	while (i < fractal->max_iterations)
	{
		temp_real = z.real;
		temp_imag = z.imag;
		z.real = temp_real * temp_real 
			- temp_imag * temp_imag + fractal->c.real;
		z.imag = 2 * temp_real * temp_imag + fractal->c.imag;
		if (z.real * z.real + z.imag * z.imag > 4)
			break ;
		i++;
	}
	clr = assign_color(i, fractal);
	ft_mlx_pixel_put(&fractal->img, x, y, clr);
}

void	julia(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	int			i;
	double		clr;
	double		temp_real;
	double		temp_imag;

	i = -1;
	fractal->max_iterations = 400;
	z.real = resize_scale(x, WIDTH, fractal->center_r -2 * fractal->zoom, 
			fractal->center_r + 2 * fractal->zoom);
	z.imag = resize_scale(y, HEIGHT, fractal->center_i - 2 * fractal->zoom, 
			fractal->center_i + 2 * fractal->zoom);
	while (i++ < fractal->max_iterations)
	{
		temp_real = z.real;
		temp_imag = z.imag;
		z.real = temp_real * temp_real 
			- temp_imag * temp_imag + fractal->c.real;
		z.imag = 2 * temp_real * temp_imag + fractal->c.imag;
		if (z.real * z.real + z.imag * z.imag > 4)
			break ;
	}
	clr = assign_color(i, fractal);
	ft_mlx_pixel_put(&fractal->img, x, y, clr);
}

static void	check_boundary(int x, int y, int j, t_fractal *fractal)
{
	if (j == 0)
		ft_mlx_pixel_put(&fractal->img, x, y, fractal->color.r);
	if (j == 1)
		ft_mlx_pixel_put(&fractal->img, x, y, fractal->color.g);
	if (j == 2)
		ft_mlx_pixel_put(&fractal->img, x, y, fractal->color.b);
	return ;
}

void	newton(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	int			i;
	int			j;

	fractal->max_iterations = 300;
	fractal->tolerance = 0.0001;
	i = -1;
	z.real = resize_scale(x, WIDTH, fractal->center_r -2 * fractal->zoom, 
			fractal->center_r + 2 * fractal->zoom);
	z.imag = resize_scale(y, HEIGHT, fractal->center_i - 2 * fractal->zoom, 
			fractal->center_i + 2 * fractal->zoom);
	while (i++ < fractal->max_iterations)
	{
		calculate_newton(&z, 0.0, 0.0);
		j = -1;
		while (++j < 3)
		{
			if (check_difference(z, fractal->roots[j], fractal->tolerance))
			{
				check_boundary(x, y, j, fractal);
				return ;
			}
		}
	}
	ft_mlx_pixel_put(&fractal->img, x, y, 0x000000);
}
