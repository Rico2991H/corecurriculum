/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:23:36 by rhoogend          #+#    #+#             */
/*   Updated: 2025/10/27 13:00:45 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
# include <signal.h>
# include "Libft/libft.h"

typedef enum
{
	OPERATORS,
	PARENT,
	REDIRECT,
	STRING,
}	token_enum;

typedef enum e_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_GROUP,
	NODE_ASSIGNMENT,
	NODE_REDIRECT,
} NodeType;

typedef struct s_token
{
	token_enum token_type;
	char    *str;
	int		s_quote;
	int		d_quote;
	struct s_token *next;

}   t_token;

typedef struct s_variables
{
	char	*name;
	char	*value;
	struct s_variables	*next;
}	t_variables;

typedef struct s_redirection
{
	char	*arrow;
	char	*name;
	char	*hdinput;
	struct	s_redirection	*next;	
} t_redirection;

typedef	struct s_expression
{
	NodeType Type;
	t_variables	*assignment;
	t_redirection *red;
	char *value;
	char	**split_paths;
	char **arg;
	char *flag;
	struct s_expression *left;
	struct s_expression *right;
	struct s_expression *child;
} t_expression;

typedef struct s_heredoc
{
	char *input;
} t_heredoc;

int 	token_counter(char *arg);
void 	tokenizer(t_token *token, char *arg);
int		isspecial(char c); 
//void    alloc_array(char *array, int i);
void	history(char *input);
void	signal_set(void);
void	val_pars(t_token *token_list, char *path);


#endif
