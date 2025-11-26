/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokencounter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:32:06 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/24 11:08:26 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*function to count double comma string*/

void	c_double_comma(char *arg, int *i, int *j)
{
	(*j)++;
		while (arg[*j])
		{	
			if (arg[*j] == 34)
			{
				(*j)++;
				(*i)++;
				break;
			}
			(*j)++;
		}
}

void	c_single_comma(char *arg, int *i, int *j)
{
	(*j)++;
	while (arg[*j])
	{	
		if (arg[*j] == 39)
		{
			(*j)++;
			(*i)++;
			break;
		}
		(*j)++;
	}
}

void	c_pipes_and_or(char *arg, int *i, int *j)
{
	int	counter;
	
	counter = 0;
	(*i)++;
	while(arg[*j] == 124)
	{
		(*j)++;
		counter++;
		if (counter > 2)
			printf("syntax error near unexpected token `|'");
	}
}
void	c_andoperators(char *arg, int *i, int *j)
{
	int	counter;
	
	counter = 0;
	(*i)++;
	while(arg[*j] == 38)
	{
		(*j)++;
		counter++;
		if (counter > 2)
			printf("syntax error near unexpected token `&'");
	}
}

void	c_redir_l(char *arg, int *i, int *j)
{
	int	counter;
	counter = 0;
	(*i)++;
	while(arg[*j] == 60)
	{
		(*j)++;
		counter++;
		if (counter > 2)
		{
			printf("syntax error near unexpected token `<'");
			exit(1);
		}
	}
}

void	c_redir_r(char *arg, int *i, int *j)
{
	int	counter;
	
	counter = 0;
	(*i)++;
	while(arg[*j] == 62)
	{
		(*j)++;
		counter++;
		if (counter > 2)
		{
			printf("syntax error near unexpected token `>'");
			exit(1);
		}
	}
}

void	c_dollarsigns(char *arg, int *i, int *j)
{
	(*j)++;
	if (arg[*j] == 63)
	{
		(*i)++;
		return;
	}
	else
	{
		while(arg[*j] != 32)
			(*j)++;
	}
}

void	c_string(char *arg, int *i, int *j)
{
	(*i)++;
	while(arg[*j] && arg[*j] > 32 && !isspecial(arg[*j]))
		(*j)++;
}

void	c_group(int *i, int *j)
{
	(*i)++;
	(*j)++;
}
int	isspecial(char c)
{
	return (c == '>' || c == '<' ||
		c == ')' || c == '(' || c == '&' ||
		c == '|' || c == '\'' || c == '"');
}
/*token_counter functions count the amount of tokens*/
int	token_counter(char *arg)
{
	int		i = 0;
	int		j = 0;
	
	while(arg[j])
	{
		while (arg[j] == 32)    //skipping the whitespace
			j++;
		if (arg[j] == 34) //count token string with double comma
			c_double_comma(arg, &i, &j);
		else if (arg[j] == 39) //count token string with single comma
			c_single_comma(arg, &i, &j);
		else if (arg[j] == 124) // count pipes and or operators
			c_pipes_and_or(arg, &i, &j);
		else if (arg[j] == 38) // count & operators
			c_andoperators(arg, &i, &j);
		else if (arg[j] == 40 || arg[j] == 41) // find groupsign(
			c_group(&i, &j);
		else if (arg[j] == 60) // find redirectors < and <<
			c_redir_l(arg, &i, &j);
		else if (arg[j] == 62) // find redirecors >> and >
			c_redir_r(arg, &i, &j);
		else if (arg[j] > 32 && !isspecial(arg[j]))
			c_string(arg, &i, &j);
	}
	return(i);
}

