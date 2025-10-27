/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:25:22 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/15 10:26:11 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printchar(char c);
int		ft_printstring(char *str);
int		ft_printhexdec(unsigned int n, const char *format);
int		ft_printnumber(int n);
int		ft_printptr(void *ptr);
int		ft_printunsint(unsigned int nbr);
int		ft_printf(const char *format, ...);

#endif 
