/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:31:34 by dmungunt          #+#    #+#             */
/*   Updated: 2025/11/10 11:46:24 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*new_node_red(t_redirection **node)
{
		t_redirection *temp;
		t_redirection *new_node;

		temp = *node;
		new_node = malloc(sizeof(t_redirection));
		if (!new_node)
			return(NULL);
		new_node->name = NULL;
		new_node->arrow = NULL;
		new_node->next = NULL;
		if (*node == NULL)
			return(new_node);
		else
		{
			while (temp->next)
				temp = temp->next;
			temp->next = new_node;
			return(temp->next);
		}
}

void	assign_red_type(t_token *token_list, t_redirection **current)
{
	if(!ft_strncmp((*current)->arrow, "<<", 2))
	{
		(*current)->Type = HEREDOC;
		(*current)->s_quote = token_list->s_quote;
		(*current)->hdinput = heredocinput(token_list->next->str);
	}
	else if (!ft_strncmp((*current)->arrow, "<", 1))
		(*current)->Type = LEFT;
	if(!ft_strncmp((*current)->arrow, ">>", 2))
		(*current)->Type = APP_RIGHT;
	else if (!ft_strncmp((*current)->arrow, ">", 1))
		(*current)->Type = RIGHT;
}

void	assign_red(t_token *token_list, t_redirection **current)
{
	t_token *temp1;
	t_redirection *extract;
	
	temp1 = token_list;
	extract = NULL;
	while(temp1) //Something
	{
		if (temp1->token_type == REDIRECT)
		{
			*current = new_node_red(&extract);
			(*current)->arrow = temp1->str;
			assign_red_type(temp1, current);
			temp1 = temp1->next;
			if (!temp1)
				break;
			(*current)->name = temp1->str;
			temp1 = temp1->next;
		}
		else
			temp1 = temp1->next;
	}	
}

t_redirection 	*extr_pars_red(t_token *token_list)
{
	t_redirection *current;
	t_token *temp2;
	t_token *temp3;

	temp2 = token_list;
	current = NULL;
	assign_red(token_list, &current);
	while(temp2 && temp2->next)
	{
		if (temp2->next->token_type == REDIRECT)
		{
			temp3 = temp2->next;
			temp2->next = temp3->next->next;
			free(temp3->next);
			free(temp3);	
		}
		else
			temp2 = temp2->next;
	}
	return (current);
}