/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:58:35 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/20 15:02:04 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

unsigned char swap_bits(unsigned char octet)
{
	unsigned char res;
	res = (octet >> 4 | octet << 4);
	return (res);
} 

unsigned char  reverse_bits(unsigned char octet)
{
	int i = 8;
	unsigned char res;
	unsigned char temp;
	while ( i-- != 0)
	{
		res = (res << 1 | octet & 1);
		octet = (octet >> 1);
	}
	return (res);
}
void print_bits(unsigned char octet)
{
	int i = 8;
	unsigned char res;
	while (i-- != 0)
	{
		res = (octet >> i & 1) + '0';
		write(1, &res, 1);
	}
}

int main()
{
	unsigned char res = reverse_bits(1);
	res = swap_bits(1);
	print_bits(res);
}

