/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:06:08 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/13 09:33:59 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* @brief This is where the image is rendered 
*		for every pixel on a x,y coordinate system 
*  		we calculate the color of the pixel and render it.
*	@param: A struct named fractal that contains several variables
*	@param: x represents the horizontals
*	@param: y represents the verticals
*/
void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	init_roots(fractal->roots);
	while (++y < HEIGHT)
	{
		if (*fractal->name == 'm')
			fractal->c.imag = resize_scale(y, HEIGHT, fractal->center_i 
					- 2 * fractal->zoom, fractal->center_i + 2 * fractal->zoom);
		x = -1;
		while (++x < WIDTH)
		{
			if (*fractal->name == 'j')
				julia(x, y, fractal);
			else if (*fractal->name == 'm')
			{
				fractal->c.real = resize_scale(x, WIDTH, fractal->center_r -2 * 
						fractal->zoom, fractal->center_r + 2 * fractal->zoom);
				mandlebrot(x, y, fractal);
			}
			else
				newton(x, y, fractal);
		}
	}
}
