/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:04:39 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/25 10:25:07 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

static int	none_valid_letters(char c)
{
	if (c < 48 || (c > 57 && c < 65) || (c > 90 && c < 97) || c > 122)
		return (1);
	return (0);
}

int	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] >= '0' && str[i] <= '9')
		return (1);
	while (str[i])
	{
		if (none_valid_letters(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	execute_export(t_expression *cmdparse, t_env **envp, t_variables **assign)
{
	int	ret;

	ret = 0;
	if (!cmdparse->args)
		print_export(envp);
	else if (!update_env(cmdparse, envp))
		update_assign(cmdparse, assign);
	else
	{
		ret = export_env(cmdparse, envp);
		if (!ret)
			export_assign(cmdparse, assign);
	}
	return (ret);
}

int	execute_env(t_env **envp)
{
	t_env	*tmp;

	tmp = *envp;
	while (tmp)
	{
		printf("%s=%s\n", tmp->before_equal, tmp->after_equal);
		tmp = tmp->next;
	}
	return (0);
}
