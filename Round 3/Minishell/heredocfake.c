/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:47:30 by rhoogend          #+#    #+#             */
/*   Updated: 2025/10/15 10:08:24 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_cmd
{
    char    **path;
    char    **tokens;
	int		fd;
}   t_cmd;

size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i ;

	i = 0;
	while (i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		if (s1[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ptr;
	size_t	i;
	size_t	j;

	j = ft_strlen((char *)s1);
	i = 0;
	len = j + ft_strlen((char *)s2);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < j)
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (j != len)
	{
		ptr[j] = s2[i];
		j++;
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char    *heredocnew(char *delimiter)
{
	char *docarg;
	char *input = "";
    while((docarg = readline("heredoc> ")) != NULL && ft_strncmp(docarg, delimiter, ft_strlen(delimiter)))
        {	        
			input = ft_strjoin(input, docarg);
            input = ft_strjoin(input, "\n");
        }
    return(input);
}
