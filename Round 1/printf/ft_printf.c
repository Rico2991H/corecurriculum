/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:57:48 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/22 13:59:21 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "ft_printf.h"

static void	format_check(va_list args, int *counter, const char *format)
{
	if (*format == '%')
	{
		ft_putchar_fd('%', 1);
		(*counter)++; 
	}
	else if (*format == 'c')
		*counter += ft_printchar(va_arg(args, int));
	else if (*format == 's')
		*counter += ft_printstring(va_arg(args, char *));
	else if (*format == 'x')
		*counter += ft_printhexdec(va_arg(args, unsigned int), format);
	else if (*format == 'X')
		*counter += ft_printhexdec(va_arg(args, unsigned int), format);
	else if (*format == 'd' || *format == 'i')
		*counter += ft_printnumber(va_arg(args, int));
	else if (*format == 'p') 
		*counter += ft_printptr(va_arg(args, void *));
	else if (*format == 'u')
		*counter += ft_printunsint(va_arg(args, unsigned int));
}

int	ft_printf(const char *format, ...)
{
	int		counter;
	va_list	args;

	counter = 0;
	va_start(args, format);
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			format_check(args, &counter, format);
		}
		else 
		{
			ft_putchar_fd(*format, 1);
			counter++;
		}
		format++;
	}
	va_end(args);
	return (counter);
}
/*# include <stdio.h>
int main(void){ 
int random;
//char random2[] = "Hello world";
//int *ptr = &random;
//char *ptr2 = random2;
random = printf("this is print %x ", 10);
printf("printf counter is %d", random);
random = ft_printf("this is print: %x ", 10);
printf("ft_printf counter is %d", random);
}*/
