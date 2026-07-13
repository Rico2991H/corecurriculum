/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:51:51 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/13 14:11:36 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

void	expand_cmd_question(t_expression *cmds_trav, int e)
{
	char	*new;

	if (e == START)
		e = 0;
	new = ft_itoa(e);
	free(cmds_trav->value);
	cmds_trav->value = new;
}

int	find_varname(char	*s1)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s1[i]) && s1[i] != '_')
		return (0);
	i++;
	while (ft_isalnum(s1[i]) || s1[i] == '_')
		i++;
	return (i);
}
