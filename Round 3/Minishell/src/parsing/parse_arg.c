/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:36:02 by dmungunt          #+#    #+#             */
/*   Updated: 2025/11/18 13:20:58 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg_node(t_arg **arg, t_token *token_list)
{
	t_arg	*new_arg;

	new_arg = malloc(sizeof(t_arg));
	if(!new_arg)
		exit(1);
	new_arg->arg = token_list->str;
	new_arg->d_quote = token_list->d_quote;
	new_arg->s_quote = token_list->s_quote;
	//new_arg->to_remove = 0;
	new_arg->next = NULL;
	if(*arg == NULL)
	{
		*arg = new_arg;
		return;
	}
	while ((*arg)->next != NULL)
	{
		*arg = (*arg)->next;
	}
	(*arg)->next = new_arg;
}

t_token	*parse_arg(t_token *token_list, t_expression **cmd_parse)
{	
	t_arg	*args;

	args = NULL;
	int		i;
	t_token *temp;

	i = 0;
	temp = token_list;
	while (token_list && token_list->token_type == STRING)
	{
		add_arg_node(&args, token_list);
		token_list = token_list->next;
		printf("adding args\n");
	}
	(*cmd_parse)->args = args;
	return(token_list);
}