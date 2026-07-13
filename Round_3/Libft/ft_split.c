/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:48:34 by dmungunt          #+#    #+#             */
/*   Updated: 2025/05/16 16:02:57 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free_str(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (0);
}

static char	*ft_put_word(char *word, char const *s, int i, int len)
{
	int	j;

	j = 0;
	while (len > 0)
	{
		word[j] = s[i - len];
		j++;
		len--;
	}
	word[j] = '\0';
	return (word);
}

static char	**ft_split_words(char const *s, char c, 
		char **new_str, int word_count)
{
	int	i;
	int	word;
	int	len;

	i = 0;
	word = 0;
	len = 0;
	while (word < word_count)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			len++;
		}
		new_str[word] = (char *)malloc(sizeof(char) * (len + 1));
		if (new_str[word] == NULL)
			return (ft_free_str(new_str, word));
		ft_put_word(new_str[word], s, i, len);
		len = 0;
		word++;
	}
	new_str[word] = 0;
	return (new_str);
}

static int	ft_word_counter(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char			**new_str;
	unsigned int	word_count;

	if (!s)
		return (0);
	word_count = ft_word_counter(s, c);
	new_str = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (new_str == NULL)
		return (NULL);
	new_str = ft_split_words(s, c, new_str, word_count);
	return (new_str); 
}
