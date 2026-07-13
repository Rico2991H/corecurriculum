/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:34:41 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/19 14:55:48 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

static int	expand_len(char *src, t_variables *vars, int *i)
{
	int			len;
	t_variables	*tmp;

	len = 0;
	while ((src[1 + len] && ft_isalnum(src[1 + len])) || src[1 + len] == '_')
		len++;
	tmp = vars;
	while (tmp)
	{
		if ((int)ft_strlen(tmp->name) == len 
			&& !ft_strncmp(tmp->name, src + 1, len))
		{
			*i += len + 1;
			return (ft_strlen(tmp->value));
		}
		tmp = tmp->next;
	}
	*i += len + 1;
	return (0);
}

static int	findendlength(char *s1, t_variables *ass, t_quote q)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s1[i])
	{
		if ((q == Q_DOUBLE || q == Q_NONE) && s1[i] == '$' && 
			dollar_sign_checks(&s1[i]) == 1)
		{
			len += expand_len(&s1[i], ass, &i);
			continue ;
		}
		else
			len++;
		i++;
	}
	return (len);
}

char	*clean_value(char *s1, t_variables *assignments, t_quote q, int e)
{
	char	*ret;
	int		i;
	int		j;
	int		totallength;

	j = 0;
	i = 0;
	if (!s1)
		return (NULL);
	if (e == START)
		e = 0;
	s1 = fill_ret_question_mark(s1, e, q);
	totallength = findendlength(s1, assignments, q);
	ret = malloc(totallength + 1);
	if (!ret)
		return (NULL);
	ret = fill_ret(ret, s1, assignments, q);
	free(s1);
	return (ret);
}

static void	create_assign(t_token *token_list, t_variables **assignment)
{
	char		**key_val;
	char		*val;
	t_variables	*temp;
	t_variables	*new_assignment;

	temp = *assignment;
	new_assignment = malloc(sizeof(t_variables));
	if (!new_assignment)
		return ;
	key_val = ft_split(token_list->segment->str, '=');
	new_assignment->name = ft_strdup(key_val[0]);
	val = ft_strdup(key_val[1]);
	new_assignment->value = val;
	new_assignment->next = NULL;
	free(key_val[0]);
	free(key_val[1]);
	free(key_val);
	if (*assignment == NULL)
		*assignment = new_assignment;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new_assignment;
	}
}

t_token	*parse_assign(t_token *token_list, t_variables **assignment)
{
	t_token	*to_free;

	to_free = token_list;
	while (token_list && token_list->token_type == STRING 
		&& find_equals(token_list->segment->str))
	{
		create_assign(token_list, assignment);
		token_list = token_list->next;
		free(to_free);
	}
	return (token_list);
}
