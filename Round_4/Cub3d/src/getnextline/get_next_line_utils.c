/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:20:59 by rhoogend          #+#    #+#             */
/*   Updated: 2026/05/12 13:12:53 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void	remove_list(t_buf **list)
{
	t_buf	*node_to_del;

	while (*list)
	{
		node_to_del = *list;
		*list = (*list)-> next;
		free(node_to_del->str_buf);
		free(node_to_del);
	}
	*list = NULL;
}

int	check_n(t_buf **list, int *i)
{
	if (!list || !*list || !(*list)->str_buf)
		return (0);
	while ((*list)->next != NULL)
	{
		*list = (*list)->next;
	}
	while ((*list)->str_buf[*i])
	{
		if ((*list)->str_buf[*i] == '\n')
		{
			(*i)++;
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int	newline(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	len_line(t_buf *list)
{
	int		str_len;
	int		i;
	t_buf	*temp;

	temp = list;
	str_len = 0;
	while (temp != NULL)
	{
		i = 0;
		while (temp-> str_buf[i])
		{
			str_len++;
			if (temp->str_buf[i] == '\n')
				break ;
			i++;
		}
		if (temp->str_buf[i] == '\n')
			break ;
		temp = temp->next;
	}
	return (str_len);
}

void	*add_node(t_buf **list, char *line)
{
	t_buf	*new_list;
	t_buf	*lastnode;

	new_list = malloc(sizeof(t_buf));
	if (!new_list)
		return (NULL);
	new_list->str_buf = line;
	new_list->next = NULL;
	if (*list == NULL)
		*list = new_list;
	else
	{
		lastnode = *list;
		while (lastnode -> next != NULL)
		{
			lastnode = lastnode -> next;
		}
		lastnode->next = new_list;
	}
	return ((void *) 1);
}
