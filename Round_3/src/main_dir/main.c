/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:39:49 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/02 12:03:53 by dmungunt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "global.h"

static void	init_garbage(t_garbage **g, char **envp)
{
	*g = malloc(sizeof(t_garbage));
	if (!*g)
		exit(1);
	(*g)->b_env = malloc(sizeof(t_envs));
	if (!(*g)->b_env)
		exit(1);
	(*g)->b_env->env = copy_env(envp);
	update_shlvl(&(*g)->b_env->env);
	(*g)->a_lst = copy_env_to_alist((*g)->b_env->env);
	(*g)->b_env->r_env = envp;
	(*g)->b_env->exit = START;
	(*g)->b_env->g = *g;
	(*g)->t_n = NULL;
}

void	print_token(t_token *token)
{
	while (token)
	{
		printf("string %s pointer %p\n ", token->str, token->str);
		token = token->next;
	}
	printf("\n");
}

static int	init_proces(t_garbage *g, char *input, char *path, int i)
{
	set_exit(&g);
	g_global_var = EXEC;
	g->t_n = create_list(i);
	if (!g->t_n)
		return (1);
	if (tokenizer(input, g->t_n))
	{
		free_tokens(g->t_n);
		g->t_n = NULL;
	}
	if (i == 1 && g->t_n->token_type == REDIRECT)
	{
		free(g->t_n->str);
		free(g->t_n);
		free_iter(g, path);
		ft_putstr_fd(
			"minishell: syntax error near unexpected token 'newline'\n", 2);
		return (1);
	}
	g->node = recursion(&g->t_n, path, g->a_lst, g);
	expansion_checker(g->node, g->a_lst, g->b_env->exit);
	g->b_env->exit = priority(g->node, &g->a_lst, g->b_env, g->b_env->exit);
	free_iter(g, path);
	g_global_var = PROMPT;
	return (0);
}

static int	run_loop(t_garbage *g, char *input, int i, char *path )
{
	int		status;

	while (1)
	{
		input = one_line_less2(&path, input, g, &status);
		if (input == NULL)
		{
			one_line_less3(g, path);
			break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		history(input);
		i = token_counter(input);
		if (!i)
		{
			one_line_less(input);
			continue ;
		}
		status = init_proces(g, input, path, i);
	}
	return (status);
}

int	main(int argc, char *argv[], char **envp)
{
	char		*input;
	t_garbage	*g;
	int			i;
	int			status;
	char		*path;

	path = NULL;
	(void)argc;
	(void)**argv;
	g = NULL;
	input = NULL;
	g_global_var = PROMPT;
	init_garbage(&g, envp);
	signal_set();
	i = 0;
	status = run_loop(g, input, i, path);
	rl_clear_history();
	return (status);
}
