/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printbits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 15:54:39 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/18 16:52:42 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

void	print_bits(unsigned char octet)
{
	int	i = 7;
	unsigned char res = octet;
	while(i > 0)
	{
		res = (octet >> i & 1) + '0';
		write (1, &res, 1);
	       i--;
	}
}

int main()
{
	print_bits(8);
}
