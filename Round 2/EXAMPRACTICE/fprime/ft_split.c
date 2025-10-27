/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:03:06 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/20 16:13:56 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

char	*alloc_words(char *str, int wordcount)
{
	int i = 0;
	int start = 0;
	char *word;
	while (str[i])
	{
		while(str[i] == 32 || str[i] == '\t' 
				|| str[i] == '\n' || str[i] == '\v')
		{
			i++;
		}
		while(str[i] > 32 && str[i] <= 126)
		{
			if (str[i - 1] == 32 || str[i - 1] == '\t' 
				|| str[i - 1] == '\n' || str[i -1] == '\v')
				start = i
			i++;
		}
		end = i;
		
		
		word = malloc(sizeof(char *) * (end - start + 1))
			
				
		
}

int	count_words(char *str)
{
	int i = 0;
	int res = 0;
	int flag = 1;
	while(str[i])
	{
		while(str[i] == 32 || str[i] == '\t' 
				|| str[i] == '\n' || str[i] == '\v')
		{
			i++;
			flag = 1;
		}
		while(str[i] > 32 && str[i] <= 126)
		{
			i++;
			if (flag ==1)
			{
				res++;
				flag = 0;
			}
		}
	}
	return(res);
}	


char **ft_split(char *str)
{
	int res = count_words(str);
	int i = 0;
	char **tab = malloc((sizeof(char *) * (res + 1)));
	if (!tab)
		return (NULL);
	while(i <= res)
	{
		tab[i] = alloc_words(str, i);
		i++;
	}
	tab[i] = NULL;
	return(tab);
}

int main()
{
	int i = 0;
	char **res = ft_split("If this works i am really happy");
	while(res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
}
