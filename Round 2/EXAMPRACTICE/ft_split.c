/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 09:49:37 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/15 10:11:00 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

fill_words

void **alloc_words(char **tab, char *str)
{
	int i = 0;
	int start = 0;
	while(str[i])
	{
		if (i == 0 && str[i] > 32 && str[i] < 127)
    			start = i;
		else if ((str[i -1] >= 9 && str[i -1] <= 11 | str[i -1] == 32) && 
			(str[i] > 32 && str[i] < 127))
			start = i;
		else if ((str[i - 1] > 32 && str[i - 1] < 127) && 
			(str[i] >= 9 && str[i] <= 11 | str[i] == 32))
			end = i;
		if ( i == end)
		{
			char *word = malloc(sizeof(char *) * (end - start + 1);
			tab[j] = fill_words(word, start, end);
			j++:
		}
		i++;
	}
}

int count_words(char *str)
{
	int in_word = 0;
	int i = 0;
	int count = 0;
	while(str[i])
	{
		if (str[i] >= 9 && str[i] <= 11 | str[i] == 32)
			in_word = 0;
		if (str[i] > 32 && str[i] < 127 && in_word == 0)
		{
			count++;
			in_word = 1;
		}
		i++;
	}
	return (count);
}
			
		

void ft_split(char *str)
{
	int count = count_words(str);
	char **tab = malloc(sizeof(char *) * (count + 1))
	if (!tab)
		return;
	return(fill_words(tab, str));
}
int main ()
{
	ft_split("       ");
}

