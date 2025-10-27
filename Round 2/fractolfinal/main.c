/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:36:12 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/11 15:36:16 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	validate_double(const char *s)
{
	int		i;
	int		dot;

	i = 0;
	dot = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9') && s[i] != '.')
			return (0);
		else if (s[i] == '.')
		{
			if (dot)
				return (0);
			dot = 1;
		}
		i++;
	}
	return (1);
}

static void	fractal_starter( t_fractal *fractal, char *name)
{
	fractal->color.r = 0xFF0000;
	fractal->color.g = 0x00FF00;
	fractal->color.b = 0x0000FF;
	fractal->name = name;
	fractal_init(fractal);
	fractal_render(fractal);
	mlx_put_image_to_window(fractal->mlx_connect, 
		fractal->mlx_window, fractal->img.img_ptr, 0, 0);
	mlx_key_hook(fractal->mlx_window, (int (*)())on_use_key, fractal);
	mlx_hook(fractal->mlx_window, 17, (1L << 17), on_press_x, fractal);
	mlx_mouse_hook(fractal->mlx_window, mouse_zoom, fractal);
	mlx_loop(fractal->mlx_connect);
}

static int	minus_checker(int *i, const char *nptr)
{
	int	sign;

	sign = 1;
	if (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
		{
			sign = -1;
			(*i)++;
			return (sign);
		}
		(*i)++;
	}
	return (sign);
}

static double	ft_strtod(const char *nptr, int i)
{
	double	number;
	double	fract;
	int		sign;
	double	divisor;

	divisor = 10;
	number = 0;
	fract = 0;
	sign = minus_checker(&i, nptr);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] == '.')
	{
		i++;
		while (nptr[i] >= '0' && nptr[i] <= '9')
		{
			fract = fract + (nptr[i] - '0') / divisor;
			divisor = divisor * 10;
			i++;
		}
	}
	return ((number + fract) * sign);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	fractal_init_struct(&fractal);
	fractal.zoom = 1.0;
	if (argc == 4)
	{
		if (validate_double(argv[2]) && validate_double(argv[3]))
		{
			fractal.c.real = ft_strtod(argv[2], 0);
			fractal.c.imag = ft_strtod(argv[3], 0);
		}
	}
	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", 5))
		|| (argc == 2 && !ft_strncmp(argv[1], "newton", 6)))
	{
		fractal_starter(&fractal, argv[1]);
	}
	else
		ft_putstr_fd(ERROR_MESSAGE, 1);
	return (0);
}
