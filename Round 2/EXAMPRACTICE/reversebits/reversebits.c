/**************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reversebits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 14:53:19 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/18 15:50:35 by rhoogend         ###   ########.fr       */
/*                                                                            */
/*************************************************************************** */

#include <stdio.h>

unsigned char	reverse_bits(unsigned char octet)
{

	int result = 0;
	int i = 8;
	while (i > 0)
	{
		result = (result << 1 | octet & 1);
		octet = octet >> 1;
		i--;
	}
	return (result); 
}
int main()
{	
	int i = 8;
	int result = reverse_bits(1);
	while ( i > 0)
	{
		unsigned char bit = (result >> i) & 1;
		printf("%d", bit);
		i--;
	}
}


