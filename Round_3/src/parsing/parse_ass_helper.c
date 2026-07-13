/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ass_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:04:54 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/16 10:41:07 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

/*static int	len_dif(char *s1, t_variables *assignment)
{
	int			len;
	int			len_new;
	t_variables	*tmp;

	len = 0;
	len_new = 0;
	while (ft_isalnum(s1[1 + len]) || s1[1 + len] == '_')
		len++;
	tmp = assignment;
	while (tmp)
	{
		if ((int)ft_strlen(tmp->name) == len 
			&& !ft_strncmp(tmp->name, s1 + 1, len))
		{
			len_new = ft_strlen(tmp->value);
			return (len_new - len);
		}
		tmp = tmp->next;
	}
	return (0);
}*/

int	get_number(int e)
{
	char	*number;
	int		number_len;

	number_len = 0;
	number = ft_itoa(e);
	number_len = ft_strlen(number);
	free(number);
	return (number_len);
}

int	find_len(char *s1, int e, t_quote q)
{
	int		len;
	int		number_len;
	int		i;

	i = 0;
	len = 0;
	number_len = get_number(e);
	while (s1[i])
	{
		if ((q == Q_DOUBLE || q == Q_NONE)
			&& s1[i] == '$' && s1[i] == '?')
		{
			if (number_len == 3)
				len += 1;
			if (number_len == 1)
				len -= 1;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*fill_ret_question_mark(char *s1, int e, t_quote q)
{
	char	*ret;
	int		total_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	total_len = find_len(s1, e, q);
	ret = malloc(sizeof(char) * total_len + 1);
	if (!ret)
		return (NULL);
	ret = fill_ret_question_helper(ret, s1, e, q);
	free(s1);
	return (ret);
}

char	*fill_ret(char *ret, char *s1, t_variables *ass, t_quote q)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		{
			if ((q == Q_DOUBLE || q == Q_NONE) && s1[i] == '$' && 
				dollar_sign_checks(&s1[i]) == 1)
				j += expand_into(&ret[j], &s1[i], ass, &i);
			else
			{
				ret[j++] = s1[i];
				i++;
			}
		}
	}
	ret[j] = '\0';
	return (ret);
}

int	dollar_sign_checks(char *str1)
{
	int	len;

	len = 1;
	if (!str1)
		return (1);
	while (ft_isalnum(str1[len]) || str1[len] == '_' || str1[len] == '?')
		len++;
	if (!ft_strncmp("$?", str1, 2) && len == 2)
		return (2);
	else if (len == 1 && !ft_strncmp("$", str1, 1))
		return (0);
	return (1);
}
