/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:28:58 by rhoogend          #+#    #+#             */
/*   Updated: 2025/10/24 14:06:17 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_double_comma(char *arg, int *j, t_token *tokens)
{
	(*j)++;
	int i = *j;
		while (arg[*j])
		{	
			if (arg[*j] == 34)
			{
				tokens->str = ft_substr(&arg[i], 0, (*j - i));
				tokens->token_type = STRING;
				tokens->d_quote = 1;
				(*j)++;
				break;
			}
			(*j)++;
		}
		printf("%s\n", tokens->str);
}

void	add_single_comma(char *arg, int *j, t_token *tokens)
{
	(*j)++;
	int i = *j;
	while (arg[*j])
	{	
		if (arg[*j] == 39)
		{
			tokens->str = ft_substr(&arg[i], 0, (*j - i));
			tokens->token_type = STRING;
			tokens->s_quote = 1;
			(*j)++;
			break;
		}
		(*j)++;
	}
	printf("%s\n", tokens->str);
}

void	add_pipes_and_or(char *arg, int *j, t_token *tokens)
{
	int i = *j;
	while(arg[*j] == 124)
	{
		(*j)++;
	}
	tokens->str = ft_substr(&arg[i], 0, (*j - i));
	tokens->token_type = OPERATORS;
	printf("%s\n", tokens->str);
}
void	add_andoperators(char *arg, int *j, t_token *tokens)
{
	int i = *j;
	while(arg[*j] == 38)
	{
		(*j)++;
	}
	tokens->str = ft_substr(&arg[i], 0, (*j - i));
	tokens->token_type = OPERATORS;
	printf("%s\n", tokens->str);
}

void	add_redir_l(char *arg, int *j, t_token *tokens)
{
	int i = *j;
	while(arg[*j] == 60)
	{
		(*j)++;
	}
	tokens->str = ft_substr(&arg[i], 0, (*j - i));
	tokens->token_type = REDIRECT;
	printf("%s\n", tokens->str);
}

void	add_redir_r(char *arg, int *j, t_token *tokens)
{
	int i = *j;
	while(arg[*j] == 62)
		(*j)++;
	tokens->str = ft_substr(&arg[i], 0, (*j - i));
	tokens->token_type = REDIRECT;
	printf("%s\n", tokens->str);
}

void	add_string(char *arg, int *j, t_token *tokens)
{
	int i = *j;
	while(arg[*j] && arg[*j] > 32 && !isspecial(arg[*j]))
		(*j)++;
	tokens->str = ft_substr(&arg[i], 0, (*j - i));
	tokens->token_type = STRING;
	printf("%s\n", tokens->str);
}

void	add_group(char *arg, int *j, t_token *tokens)
{
	if (arg[*j] == 40)
		tokens->str = ft_strdup("(");
	if (arg[*j] == 41)
		tokens->str = ft_strdup(")");
	tokens->token_type = PARENT;
	(*j)++;
}

void	tokenizer(t_token *tokens, char *arg) // use array to acces token holder fill with these functions something something
{
	int		j = 0;

	while(arg[j])
	{
		while (arg[j] == 32) //skipping the whitespace
			j++;
		if (!arg[j])
			break;
		if (arg[j] == 34) //count token string with double comma
			add_double_comma(arg, &j, tokens);
		else if (arg[j] == 39) //count token string with single comma
			add_single_comma(arg, &j, tokens);
		else if (arg[j] == 124) // count pipes and or operators
			add_pipes_and_or(arg, &j, tokens);
		else if (arg[j] == 38) // count & operators
			add_andoperators(arg, &j, tokens);
		else if (arg[j] == 40 || arg[j] == 41)
			add_group(arg, &j, tokens);
		else if (arg[j] == 60) // find redirectors < and <<
			add_redir_l(arg, &j, tokens);
		else if (arg[j] == 62) // find redirecors >> and >
			add_redir_r(arg, &j, tokens);
		else if (arg[j] > 32 && !isspecial(arg[j]))
			add_string(arg, &j, tokens);
		if(tokens)
			tokens = tokens->next;
		else
			break;
	}
}






