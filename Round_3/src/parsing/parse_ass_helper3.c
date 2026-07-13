/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ass_helper3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 13:54:58 by dmungunt          #+#    #+#             */
/*   Updated: 2026/02/13 14:02:45 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_into(char *dst, char *src, t_variables *vars, int *i)
{
	int			len;
	t_variables	*tmp;

	len = 0;
	while (ft_isalnum(src[1 + len]) || src[1 + len] == '_')
		len++;
	tmp = vars;
	while (tmp)
	{
		if ((int)ft_strlen(tmp->name) == len 
			&& !ft_strncmp(tmp->name, src + 1, len))
		{
			ft_memcpy(dst, tmp->value, ft_strlen(tmp->value));
			*i += len + 1;
			return (ft_strlen(tmp->value));
		}
		tmp = tmp->next;
	}
	*i += len + 1;
	return (0);
}

char	*fill_ret_question_helper(char *ret, char *s1, int e, t_quote q)
{
	int		i;
	int		j;
	char	*number;
	int		k;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if ((q == Q_DOUBLE || q == Q_NONE)
			&& s1[i] == '$' && s1[i + 1] == '?')
		{
			number = ft_itoa(e);
			k = 0;
			while (number[k])
				ret[j++] = number[k++];
			free(number);
			i += 2; 
		}
		else
			ret[j++] = s1[i++];
	}
	ret[j] = '\0';
	return (ret);
}
