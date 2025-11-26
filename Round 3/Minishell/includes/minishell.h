/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:23:36 by rhoogend          #+#    #+#             */
/*   Updated: 2025/11/26 16:07:44 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include "../Libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <fcntl.h>

# ifndef GLOBAL_H
# define GLOBAL_H

extern int global_var;

# endif

typedef enum
{
	OPERATORS,
	PARENT,
	REDIRECT,
	STRING,
	PIPE,
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
	NODE_SUBSHELL,
	NODE_SUBSHELL_END,
} NodeType;

typedef enum e_redir
{
	LEFT,
	RIGHT,
	HEREDOC,
	APP_RIGHT,
} redir_enum;

/*typedef enum
{
	OPERATORS,
	PARENT,
	REDIRECT,
	STRING,
}	token_enum;

typedef struct s_token
{
	token_enum token_type;
	char	*str;
}   t_token;*/

typedef struct s_path
{
	char	**cmd_paths;
	char	*the_path;
	char	*path;
}	t_path;

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
}	t_pipex;

typedef struct s_env
{
	char	*before_equal;
	char	*after_equal;
	struct	s_env	*next;
}	t_env;

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

typedef struct s_files
{
	char	*filename;
	struct 	s_files *next;
}	t_files;

typedef struct s_redirection
{
	redir_enum Type;
	char	*arrow;
	char	*name;
	char	*hdinput;
	int		s_quote;
	char	*path;
	struct	s_redirection	*next;	
} t_redirection;

typedef struct s_arguments
{
	char	*arg;
	int		s_quote;
	int		d_quote;
	int		to_remove;
	struct s_arguments *next;
} t_arg;

typedef	struct s_expression
{
	NodeType Type;
	t_variables	*assignment;
	t_redirection *red;
	int		fd_in;
	int		fd_out;
	char *value;
	char	**split_paths;
	t_arg *args;
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

//int 	main(int argc, char *argv[]);
int 			token_counter(char *arg);
void 			tokenizer(t_token *token, char *arg);
int				isspecial(char c); 
void			history(char *input);
void			signal_set(void);
t_expression	*val_pars(t_token **token_list, char *path);
t_expression	*recursion(t_token **token_list, char *path);
t_token			*val_pars_recursion(t_expression **result, t_token *token_list, char *path);
t_token			*subshell(t_expression **child, t_token *token_list, char *path);
void 			print_tokenlist(t_token *token_list);
t_token			*pars_operator(t_token *token_list, t_expression **cmdparse);
t_token			*parse_command(t_token *token_list, t_expression **cmdparse, t_variables **assignment, char *path);
int 			find_command(char *command, t_expression **cmdparse);
t_token			*parse_assign(t_token *token_list, t_variables **assignment);
t_redirection 	*extr_pars_red(t_token *token_list);
void			assign_red(t_token *token_list, t_redirection **current);
t_redirection	*new_node_red(t_redirection **node);
t_token			*parse_arg(t_token *token_list, t_expression **cmd_parse);
//t_token			*parse_pipe(t_token *token_list, t_expression **cmdparse);
void			create_assign(t_token *token_list, t_variables **assignment);
int				check_for_operator(char *str);
int				find_equals(t_token *token);
char    		*heredocinput(char *delimiter);
void    		expansion_checker(t_expression *cmd_parse, t_variables *assignments);
void			extract_assignments(t_expression *cmd_parse, t_variables **assignments);
int				priority(t_expression *cmdparse, t_env **envp, t_variables **assignments, char **r_envp);
void			extractor(t_expression *cmd_parse, t_variables **assignment);
t_files *		retrieve_files();
void			check_for_ast(t_expression *cmd_parse);
void			remove_ast(t_arg **arg_trav);
t_env			*copy_env(char **envp);
t_env			*env_last(t_env *lst);
t_env			*init_env(char *str);
void			append_env_list(t_env **result, t_env *new);
int				built_in(char *value);
t_files *		retrieve_files();
void			check_for_ast(t_expression *cmd_parse);
void			remove_ast(t_arg **arg_trav);
void			check_for_redirect(t_expression *parse_cmds);
void			reset_fd(t_expression *parse_cmds);
#endif