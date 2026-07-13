/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_a_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:58:09 by dmungunt          #+#    #+#             */
/*   Updated: 2026/01/29 13:43:28 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

t_variables	*a_lst_last(t_variables *lst)
{
	if (!lst)
		return (NULL);
	while (lst && lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	append_assign_lst(t_variables **ret, t_variables *new)
{
	t_variables	*last;

	if (ret == NULL)
	{
		return ;
	}
	if (*ret == NULL)
	{
		*ret = new;
		return ;
	}
	last = a_lst_last(*ret);
	last->next = new; 
}

t_variables	*dup_assign(t_variables	*assign)
{
	t_variables	*ret;

	ret = malloc(sizeof(t_variables));
	if (!ret)
		return (NULL);
	ret->name = assign->name;
	ret->value = assign->value;
	ret->next = NULL;
	return (ret);
}

t_variables	*dup_a_lst(t_variables *assignmentlist)
{
	t_variables	*tmp;
	t_variables	*ret;

	while (assignmentlist)
	{
		tmp = dup_assign(assignmentlist);
		append_assign_lst(&ret, tmp);
		assignmentlist = assignmentlist->next;
	}
	return (ret);
}
