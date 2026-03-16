/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newtonbonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:14:30 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/13 09:42:44 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* We initialize an array containing the
* the roots to which the function has to converge after iteration.
*/
void	init_roots(t_complex *roots)
{
	static int	flag;

	if (flag == 0)
	{
		roots[0] = (t_complex){1, 0};
		roots[1] = (t_complex){-0.5, sqrt(3) / 2};
		roots[2] = (t_complex){-0.5, -sqrt(3) / 2};
		flag = 1;
	}
	return ;
}

/* Some complex number algebra to assign the real and imaginary values
* 
*/
void	calculate_newton(t_complex *z, double temp_real, double temp_imag)
{
	double	znumr;
	double	znumi;
	double	deriv_r;
	double	deriv_i;
	double	denom;

	temp_real = z->real;
	temp_imag = z->imag;
	znumr = (temp_real * temp_real * temp_real) 
		- (3 * temp_real * (temp_imag * temp_imag)) - 1;
	znumi = (3 * temp_real * temp_real * temp_imag) 
		- (temp_imag * temp_imag * temp_imag);
	deriv_r = (3 * (temp_real * temp_real) - 3 * (temp_imag * temp_imag));
	deriv_i = 6 * temp_real * temp_imag;
	denom = deriv_r * deriv_r + deriv_i * deriv_i;
	temp_real = (znumr * deriv_r + znumi * deriv_i) / denom;
	temp_imag = (znumi * deriv_r - znumr * deriv_i) / denom;
	z->real = z->real - temp_real;
	z->imag = z->imag - temp_imag;
}

/* This function checks if the iteration already converged to the root
* 
*/
int	check_difference(t_complex z, t_complex root, double tolerance)
{
	t_complex	difference;
	int			flag;

	flag = 0;
	difference.real = z.real - root.real;
	difference.imag = z.imag - root.imag;
	if (fabs(difference.real) < tolerance 
		&& fabs(difference.imag) < tolerance)
		flag = 1;
	return (flag);
}
