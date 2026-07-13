/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_red.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:31:34 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/27 16:06:22 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_red_type(t_token *token_list, 
		t_redirection **current, t_garbage *g)
{
	if (!ft_strncmp((*current)->arrow, "<<", 2) 
		&& ft_strlen((*current)->arrow) == 2)
	{
		(*current)->type = HEREDOC;
		(*current)->segment = token_list->next->segment;
		(*current)->hdinput = heredocinput(token_list->next->segment->str, 
				g, current);
		return ;
	}
	else if (!ft_strncmp((*current)->arrow, "<", 1) 
		&& ft_strlen((*current)->arrow) == 1)
	{
		(*current)->type = LEFT;
		return ;
	}
	if (!ft_strncmp((*current)->arrow, ">>", 2) 
		&& ft_strlen((*current)->arrow) == 2)
		(*current)->type = APP_RIGHT;
	else if (!ft_strncmp((*current)->arrow, ">", 1) 
		&& ft_strlen((*current)->arrow) == 1)
		(*current)->type = RIGHT;
}

static void	assign_red_vals(t_token *token, t_redirection *new_node)
{
	if (token->str && token->next)
	{
		new_node->arrow = ft_strdup(token->str);
		new_node->segment = token->next->segment;
	}
	else
	{
		ft_putstr_fd(
			"minishell: syntax error near unexpected token 'newline'\n", 2);
		return ;
	}
	new_node->next = NULL;
	new_node->path = NULL;
	new_node->to_remove = 0;
	new_node->type = NO_RED;
	new_node->hdinput = NULL;
}

void	new_node_red(t_redirection **node, t_token *token, t_garbage *g)
{
	t_redirection	*temp;
	t_redirection	*new_node;

	temp = *node;
	new_node = ft_calloc(1, sizeof(t_redirection));
	if (!new_node)
		return ;
	assign_red_vals(token, new_node);
	assign_red_type(token, &new_node, g);
	if (*node == NULL)
	{
		*node = new_node;
		return ;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
		return ;
	}
}

void	assign_red(t_token *token_list, t_redirection **current, t_garbage *g)
{
	t_token			*temp1;
	t_redirection	*extract;

	temp1 = token_list;
	extract = NULL;
	while (temp1 && temp1->token_type != PIPE 
		&& temp1->token_type != OPERATORS && temp1->token_type != PARENT)
	{
		if (temp1->token_type == REDIRECT)
		{
			new_node_red(&extract, temp1, g);
			temp1 = temp1->next;
		}
		else
			temp1 = temp1->next;
	}
	*current = extract;
}

t_redirection	*extr_pars_red(t_token **token_list, t_garbage *g)
{
	t_redirection	*current;

	if (!token_list || !*token_list)
		return (NULL);
	current = NULL;
	assign_red(*token_list, &current, g);
	if (!extract_helper(token_list))
		return (NULL);
	if (!token_list)
		return (NULL);
	return (current);
}
