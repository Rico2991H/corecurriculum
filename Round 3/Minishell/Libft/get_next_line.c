/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:44:14 by rhoogend          #+#    #+#             */
/*   Updated: 2025/05/29 10:44:19 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
/*#include <stdio.h>*/
static void	copy_to_str(t_list *list, char *str)
{
	int	i;
	int	j;

	j = 0;
	while (list != NULL)
	{
		i = 0;
		while (list->str_buf[i])
		{
			str[j] = list->str_buf[i];
			if (list->str_buf[i] == '\n')
			{
				j++;
				str[j] = '\0';
				return ;
			}
			j++;
			i++;
		}
		list = list->next;
	}
	str[j] = '\0';
}

static void	*clean_node(t_list **list, int j)
{
	char	*new_buf;
	int		i;

	i = 0;
	if (check_n(list, &i))
	{
		remove_list(list);
	}
	else
	{
		while ((*list)->str_buf[i + j])
			j++;
		new_buf = malloc (sizeof(char) * (j + 1));
		if (!new_buf)
			return (NULL);
		j = 0;
		while ((*list)->str_buf[i])
			new_buf[j++] = (*list)->str_buf[i++];
		new_buf[j] = '\0';
		remove_list(list);
		add_node(list, new_buf);
	}
	return ((void *) 1);
}

static void	store_text(t_list **list, int fd)
{
	char	*buf;
	int		bytes_read;

	if (*list != NULL && newline((*list)->str_buf))
		return ;
	while (1)
	{
		buf = malloc(sizeof(char ) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		bytes_read = read(fd, buf, BUFFER_SIZE); 
		if (bytes_read <= 0)
		{
			free(buf);
			break ;
		}
		buf[bytes_read] = '\0';
		add_node(list, buf);
		if (newline(buf))
			break ;
	}
}

static char	*get_line(t_list *list)
{
	char	*copied_str;
	int		str_len;

	if (list == NULL)
		return (NULL);
	str_len = len_line(list);
	copied_str = malloc(str_len + 1);
	if (!copied_str)
		return (NULL);
	copy_to_str(list, copied_str);
	return (copied_str);
}

char	*get_next_line(int fd)
{
	int				j;
	char			*next_line;
	static t_list	*list;

	j = 0;
	if ((fd < 0) || (BUFFER_SIZE <= 0)) 
		return (NULL);
	store_text(&list, fd);
	if (list == NULL || (list && list->str_buf == NULL))
		return (NULL);
	next_line = get_line(list);
	if (!next_line || next_line[0] == '\0')
	{
		remove_list(&list); 
		/*if (list)
		{
			free(list->str_buf);
			free(list);
			list = NULL;
		}
		free(next_line);
		return (NULL);*/
	}
	if (!clean_node(&list, j))
		return (NULL);
	return (next_line);
}
/*
#include <stdio.h>
#include "get_next_line.h"

int main()
{
	int fd = open("textdebug.txt", O_RDONLY);
	char	*line = "";

	if(fd < 0)
	{
		printf("Error");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return(0);
}*/
