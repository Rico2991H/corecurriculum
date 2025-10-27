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

static void	*clean_node(t_list **list, int j, int i)
{
	char	*new_buf;
	t_list	*temp;

	temp = *list;
	if (!check_n(&temp, &i))
		remove_list(list);
	else
	{
		while (temp->str_buf[i + j])
			j++;
		new_buf = malloc (sizeof(char) * (j + 1));
		if (!new_buf)
			return (NULL);
		j = 0;
		while (temp->str_buf[i])
			new_buf[j++] = temp->str_buf[i++];
		new_buf[j] = '\0';
		remove_list(list);
		if (!add_node(list, new_buf))
		{
			free (new_buf);
			return (NULL);
		}
	}
	return ((void *) 1);
}

static void	*store_text(t_list **list, int fd, char *next_line)
{
	int		bytes_read;

	if (*list != NULL && newline((*list)->str_buf))
		return ((void *) 1);
	while (1)
	{
		next_line = malloc(sizeof(char ) * (BUFFER_SIZE + 1));
		if (!next_line)
			return (NULL);
		bytes_read = read(fd, next_line, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(next_line);
			if (bytes_read == -1)
				return (remove_list(list), NULL);
			break ;
		}
		next_line[bytes_read] = '\0';
		if (!add_node(list, next_line))
			return (free (next_line), NULL);
		if (newline(next_line))
			break ;
	}
	return ((void *) 1);
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
	int				i;
	char			*next_line;
	static t_list	*list;

	j = 0;
	i = 0;
	next_line = NULL;
	if ((fd < 0) || (BUFFER_SIZE <= 0)) 
		return (NULL);
	if (!store_text(&list, fd, next_line))
		return (NULL);
	if (list == NULL || (list && list->str_buf == NULL))
		return (NULL);
	next_line = get_line(list);
	if (!next_line || next_line[0] == '\0')
	{
		free(next_line);
		remove_list(&list); 
		return (NULL);
	}
	if (!clean_node(&list, j, i))
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
