/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rostring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:05:42 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/20 11:47:27 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void 	rostring(char *str)
{	
	int start = 0;
	int end = 0;
	int i = 0;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n' || str[i] == '\v')
	{
		i++;
	}
	start = i;
	while (str[i] > 32 && str[i] <= 126)
	{
		i++;
	}
	end = i;
        while (str[i] == 32 || str[i] == '\t' || str[i] == '\n' ||str[i] == '\v')
                i++;
	while (str[i] != '\0')
	{       
		while (str[i] > 32 && str[i] < 126)
        	{
                write(1, &str[i], 1);
                i++;
        	}
        	while (str[i] == 32 || str[i] == '\t' || str[i] == '\n' || str[i] == '\v')
		{
		i++;
		}
        write(1, " ", 1);
        }
	while(start < end)
	{
		write(1, &str[start], 1);
		start++;
	}
}


int main (int argc, char ** argv)
{
	int pos = 2;
	int i = 0;
	if (argc < 2)
		write(1, "\n", 1);
	if (argc == 2)
		rostring(argv[1]);
}
