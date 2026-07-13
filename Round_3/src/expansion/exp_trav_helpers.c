/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_trav_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 14:07:35 by rhoogend          #+#    #+#             */
/*   Updated: 2026/02/16 10:40:29 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

int	question_mark_check(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "$?", 2) == 0)
		return (1);
	return (0);
}
