/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 09:15:50 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/19 10:00:06 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_files *create_files(t_files *files)
{	
	t_files	*new_file;

	new_file = malloc(sizeof(t_files));
	if(!new_file)
		return NULL;
	new_file->filename = NULL;
	new_file->next = NULL;
	
	if (!files)
		return (new_file);
		
	while(files->next)
		files = files->next;
	files->next = new_file;
	return (new_file);
}

t_files *retrieve_files()
{
	DIR 			*dir;		
	struct dirent	*entry;
	t_files			*file;
	t_files			*head;
	
	file = NULL;
	head = NULL;
	dir = opendir(".");
	if (!dir)
		return (NULL);
		
	while((entry = readdir(dir)) != NULL)
	{
		file = create_files(file);
		file->filename = ft_strdup(entry->d_name);
		if (!head)
			head = file;
	}
	closedir(dir);
	return(head);
}

/*void	expand_ast()
{
	t_files *files;
	files = retrieve_files();
	while(files)
	{
		printf("%s\n", files->filename);
		files = files->next;
	}
}*/

int	check_before(char *arg, int i, t_files *files) // we start at an asterix in arg 
{
	int j; 
	int len;
	
	len = ft_strlen(files->filename); //start at the end of filename
	j = 0;
	if (i == 0)
		return(1);
	i--; // move out of the asterix
	if (arg[i] == files->filename[i]) //iterate backwards until its a matchs
	{
		while(i >= 0 && len >= 0 && arg[i] == files->filename[i]) //While its a match go backwards it sh
		{
			if(arg[i] != files->filename[i])
				return(0);
			i--;
			len--;
		}
		return(1);
	}
	return(0);
}

int check_after(char *arg, int i, t_files *files, int j)
{
	while(arg[i] && arg[i] == '*')
	{
		i++;
		if (!arg[i])
			return(1);
	}
	while(files->filename[j])
	{
		if(arg[i] == files->filename[j])
		{
			while(arg[i] && files->filename[j])
			{
				i++;
				j++;
				if(arg[i] == '*')
					return(check_after(arg, i, files, j));
				if(arg[i] != files->filename[j])
					return(0);
			}
			return(1);
		}
		j++;
	}
	return(0);
}

int	check_files(char *arg, int i, t_files *files)
{
	if (check_before(arg, i, files))
		if(check_after(arg, i ,files, 0))
			return(1);
	return(0);
}

void	expand_ast(t_arg **arg, char *filename)
{
	t_arg	*new_arg;
	t_arg	*tmp;
	
	tmp = *arg;
	(*arg)->to_remove = 1;
	new_arg = malloc(sizeof(t_arg));
	new_arg->d_quote = 0;
	new_arg->s_quote = 0;
	new_arg->to_remove = 0;
	new_arg->arg = ft_strdup(filename);
	new_arg->next = NULL;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new_arg;
}

void	check_for_ast(t_expression *cmd_parse)
{
	t_files *files;
	t_arg   *arg_trav;
	int		i;

	files = retrieve_files();
	arg_trav = cmd_parse->args; // copy the adres of the head of list of arguments in new var;
	i = 0;
	while(arg_trav) //traverse through new var
	{
		while(arg_trav->arg[i])
		{
			if(arg_trav->arg[i] == '*' && arg_trav->s_quote == 0 && arg_trav->d_quote == 0)
			{
				while(files)
				{
					if (check_files(arg_trav->arg, i, files)) //check for pattern recognition compare with filenames
						expand_ast( &arg_trav, files->filename); //copy adres of list of args in new function to expand including filenames
					files = files->next;
				}
			}
			i++;
		}
		i = 0;
		arg_trav = arg_trav->next;
	}
}

void	remove_ast(t_arg **arg_trav)
{
	t_arg	*curr; 
	t_arg	*prev;
	t_arg	*temp_arg;
	
	curr = *arg_trav;
	prev = NULL;
	temp_arg = NULL;
	while(curr)
	{
		if(curr->to_remove == 1)
		{
			temp_arg = curr;
			
            if (prev == NULL)
                *arg_trav = curr->next;
			else
				prev->next = curr->next;

			curr = curr->next;
			free(temp_arg);
		}
		else
		{
			prev = curr;
			curr = curr->next;	
		}
	}
}


