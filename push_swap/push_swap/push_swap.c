/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 14:29:31 by rhoogend          #+#    #+#             */
/*   Updated: 2025/06/25 17:55:49 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
#include <stdio.h>

static char	**get_input_args(int argc, char **argv, int *count)
{
	char	**split;

	if (argc == 2)
	{
		split = ft_split(argv[1], ' ');
		if (!split)
			return (NULL);
		*count = 0;
		while (split[*count])
			(*count)++;
		return (split);
	}
	else
	{
		*count = argc - 1;
		return (argv + 1);
	}
}

void	build_list(int argcount, char **args, t_list_node **lista, int argc)
{
	int	i;
	int	nbr;

	i = 0;
	while (i < argcount)
	{
		nbr = ft_atoi(args[i]);
		if (!append_node(lista, nbr, -1))
		{
			free_list(*lista);
			if (argc == 2)
				free_split(args);
			exit (1);
		}
		i++;
	}
	if (is_sorted(*lista))
	{
		free_list(*lista);
		if (argc == 2)
			free_split(args);
		exit (1);
	}
}

static int	chunkcount(int list_len)
{
	if (list_len <= 20)
		return (2);
	if (list_len <= 100)
		return (10);
	if (list_len > 100 && list_len <= 300)
		return (14);
	if (list_len > 300 && list_len <= 500)
		return (11);
	return (-1);
}

void	push_swap(t_list_node **list)
{
	int	listlen;
	int	numchunks;
	int	chunksize;

	listlen = count_list(list);
	if (listlen <= 2 && (*list)->nb < (*list)->next->nb && listlen != 1)
		swap(*list);
	label_numbers(list);
	if (listlen == 3)
		sort3(list);
	if (listlen == 4 || listlen == 5)
		sort5(list);
	if (listlen > 5)
	{
		numchunks = chunkcount(listlen);
		chunksize = (listlen + numchunks -1) / numchunks;
		sort(list, numchunks, listlen, chunksize);
	}
	else
		return ;
}

int	main(int argc, char **argv)
{
	t_list_node		*lista;
	char			**args;
	int				argcount;

	lista = NULL;
	if (argc <= 1)
		return (1);
	args = get_input_args(argc, argv, &argcount);
	if (!args)
		return (1);
	int_check(argcount, args);
	doublenum_check(argcount, args);
	build_list (argcount, args, &lista, argc);
	push_swap(&lista);
	free_list(lista);
	return (0);
}
