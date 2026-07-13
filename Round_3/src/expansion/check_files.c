/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:33:25 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/03 11:27:02 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

static t_files	*create_files(t_files *files)
{
	t_files	*new_file;
	t_files	*tmp;

	new_file = malloc(sizeof(t_files));
	if (!new_file)
		return (NULL);
	new_file->filename = NULL;
	new_file->next = NULL;
	if (!files)
		return (new_file);
	tmp = files;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_file;
	return (new_file);
}

/*static t_files	*iter_dir(struct dirent *entry, DIR *dir)
{
	t_files			*file;
	t_files			*head;

	file = NULL;
	head = NULL;
	while (entry != NULL)
	{
		file = create_files(file);
		file->filename = ft_strdup(entry->d_name);
		if (!file->filename)
		{
			free(file);
			break ;
		}
		if (!head)
			head = file;
		entry = readdir(dir);
	}
	return (head);
}*/

static int	if_not_file(t_files *file)
{
	if (!file->filename)
	{
		free(file);
		return (1);
	}
	return (0);
}

t_files	*retrieve_files(void)
{
	DIR				*dir;		
	struct dirent	*entry;
	t_files			*file;
	t_files			*head;

	file = NULL;
	head = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry != NULL)
	{
		file = create_files(file);
		file->filename = ft_strdup(entry->d_name);
		if (if_not_file(file))
			break ;
		if (!head)
			head = file;
		entry = readdir(dir);
	}
	closedir (dir);
	return (head);
}

int	check_files(char *arg, int i, t_files *files)
{
	if (check_before(arg, i, files))
		if (check_after(arg, i, files, 0))
			return (1);
	return (0);
}
