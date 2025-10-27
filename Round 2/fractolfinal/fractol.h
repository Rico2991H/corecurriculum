/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:40:43 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/11 15:35:57 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include "libft.h"

# define ERROR_MESSAGE "Accepted input == julia <val1> <val2>\
, newton or mandelbrot"

# define WIDTH 800
# define HEIGHT 800

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels;
	int		bitspp;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
	double	colorfader;
}	t_rgb;

typedef struct s_fractal
{
	char		*name;
	void		*mlx_connect;
	void		*mlx_window;
	t_img		img;
	int			max_iterations;
	double		center_r;
	double		center_i;
	double		zoom;
	double		tolerance;
	t_complex	c;
	t_complex	z;
	t_complex	roots[3];
	t_rgb		color;
}	t_fractal;

void	fractal_init(t_fractal *fractal);
void	fractal_render(t_fractal *fractal);
void	julia(int x, int y, t_fractal *fractal);
void	mandlebrot(int x, int y, t_fractal *fractal);
double	assign_color(int i, t_fractal *fractal);
int		on_use_key(int keysym, t_fractal *param);
int		on_press_x(t_fractal *fractal);
int		mouse_zoom(int button, int x, int y, t_fractal *fractal);
int		check_difference(t_complex z, t_complex root, double tolerance);
void	calculate_newton(t_complex *z, double temp_real, double temp_imag);
void	init_roots(t_complex *roots);
double	resize_scale(double orig_nbr, double max_pixel, 
			double new_min, double new_max);
void	ft_mlx_pixel_put(t_img	*data, int x, int y, int color);
void	newton(int x, int y, t_fractal *fractal);
void	fractal_init_struct(t_fractal *f);

#endif
