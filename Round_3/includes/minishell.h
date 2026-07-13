/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmungunt <dmungunt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 10:23:36 by rhoogend          #+#    #+#             */
/*   Updated: 2026/03/02 12:12:34 by dmungunt         ###   ########.fr       */
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
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>
# define START 888
# define PROMPT 0
# define EXEC 1

typedef struct s_envs		t_envs;
typedef struct s_garbage	t_garbage;

typedef enum e_quote
{
	Q_NONE = 0,
	Q_SINGLE = 1,
	Q_DOUBLE = 2,
}	t_quote;

typedef struct s_hd_info
{
	int		status;
	int		fd[2];
	char	buf[1025];
	char	*docarg;
	char	*input;
	char	*tmp;
	int		n;
}	t_hd_info;

typedef struct s_qcheck
{
	int			i;
	int			in_single;
	int			in_double;
	int			prev_single;
	int			prev_double;
	t_quote		cur_q;
}	t_qcheck;

typedef enum e_token
{
	NOTHING,
	OPERATORS,
	PARENT,
	REDIRECT,
	STRING,
	PIPE,
}	t_etoken;

typedef enum e_type
{
	NODE_COMMAND = 0,
	NODE_PIPE = 1,
	NODE_AND = 2,
	NODE_OR = 3,
	NODE_GROUP = 4,
	NODE_ASSIGNMENT = 5,
	NODE_REDIRECT = 6,
	NODE_SUBSHELL = 7,
	NODE_SUBSHELL_END = 8,
}	t_NodeType;

typedef enum e_redir
{
	LEFT,
	RIGHT,
	HEREDOC,
	APP_RIGHT,
	NO_RED,
}	t_eredir;

typedef struct s_segment
{
	char				*str;
	t_quote				quote;
	struct s_segment	*next;
}	t_segment;

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

typedef struct s_token
{
	t_etoken		token_type;
	char			*str;
	t_segment		*segment;
	struct s_token	*next;

}	t_token;

typedef struct s_variables
{
	char				*name;
	char				*value;
	struct s_variables	*next;
}	t_variables;

typedef struct s_files
{
	char			*filename;
	struct s_files	*next;
}	t_files;

typedef struct s_redirection
{
	t_eredir				type;
	char					*arrow;
	char					*name;
	char					*hdinput;
	int						to_remove;
	char					*path;
	t_segment				*segment;
	struct s_redirection	*next;	
}	t_redirection;

typedef struct s_arguments
{
	char				*arg;
	int					to_remove;
	int					expand_question;
	t_segment			*segment;
	struct s_arguments	*next;
}	t_arg;

typedef struct s_pids
{
	pid_t	pid[256];
	int		count;
	pid_t	last_pid;
}	t_p;

typedef struct s_expression
{
	t_NodeType			type;
	t_variables			*assignment;
	t_redirection		*red;
	int					fd_in;
	int					fd_out;
	int					fd_in_backup;
	int					fd_out_backup;
	char				*value;
	char				**split_paths;
	t_arg				*args;
	char				*flag;
	t_segment			*segment;
	t_garbage			*g;
	struct s_expression	*left;
	struct s_expression	*right;
	struct s_expression	*child;
}	t_expression;

typedef struct s_garbage
{
	t_envs			*b_env;
	t_token			*t_n;
	t_expression	*node;
	t_variables		*a_lst;
}	t_garbage;

typedef struct s_heredoc
{
	char	*input;
}	t_heredoc;

typedef struct s_env
{
	char			*before_equal;
	char			*after_equal;
	struct s_env	*next;
}	t_env;

typedef struct s_envs
{
	t_env		*env;
	char		**r_env;
	t_garbage	*g;
	int			exit;
}	t_envs;

// one_line.c
void			one_line_less(char *input);
char			*one_line_less2(char **path, char *input, 
					t_garbage *g, int *status);
void			one_line_less3(t_garbage *g, char *path);

// init_tokenlist.c
t_token			*create_list(int i);

// token_check.c
void			token_check(t_token *token_list);

// extra_tokencounter.c
int				c_pipes_and_or(char *arg, int *i, int *j, t_etoken *is_op);
int				c_andoperators(char *arg, int *i, int *j, t_etoken *is_op);
int				c_redir_l(char *arg, int *i, int *j);
int				c_redir_r(char *arg, int *i, int *j);
int				token_counter(char *arg);

//tokenizer3.c
void			add_string(char *arg, int *j, t_token *tokens);
void			add_segment(t_token *token, char *str, int len, t_quote quote);
void			ass_q(int in_single, int in_double, t_quote *cur_q);
void			chang_i_j(int *j, int *i);

//tokenizer2.c
void			add_pipes_and_or(char *arg, int *j, t_token *tokens);
void			add_andoperators(char *arg, int *j, t_token *tokens);
void			add_redir_l(char *arg, int *j, t_token *tokens);
void			add_redir_r(char *arg, int *j, t_token *tokens);
int				if_group(int group);

//tokenizer.c
int				tokenizer(char *arg, t_token *tokens);
int				isspecial(char c);
int				isoperator(char c);
t_token			*subshell(t_expression **child,
					t_token *token_list, char *path);
void			check_all(t_qcheck *check, t_token *tokens, int *j, char *arg);

// parsing .c
t_expression	*val_pars(t_token **token_list, 
					char *path, t_variables *assign, t_garbage *g);
char			*heredocinput(char *delimiter, 
					t_garbage *g, t_redirection **red);

// pars_red.c
t_redirection	*extr_pars_red(t_token **token_list, t_garbage *g);
void			assign_red(t_token *token_list, 
					t_redirection **current, t_garbage *g);
void			new_node_red(t_redirection **node, 
					t_token *token, t_garbage *g);

// parse_arg.c
t_token			*parse_arg(t_token *token_list, t_expression **cmd_parse);

// parse_assign.c
t_token			*parse_assign(t_token *token_list, t_variables **assignment);
char			*clean_value(char *s1, 
					t_variables *assignment, t_quote q, int e);

// parse_cmd.c
t_token			*parse_command(t_token *token_list, t_expression **cmdparse,
					t_variables **assignment, char *path);
int				find_command(char *command, t_expression *cmdparse);

// parse_op.c
t_token			*pars_operator(t_token **token_list,
					t_expression **cmdparse);
int				check_for_operator(char *str);

// pars_red_helper.c
int				extract_helper(t_token **curr);

//parse_ass_helper.c
int				endlength_helper(int *quot_count, int len,
					char *s1, t_variables *ass);
char			*fill_ret(char *ret, char *s1, t_variables *ass, t_quote q);
int				dollar_sign_checks(char *str1);
char			*fill_ret_question_mark(char *s1, int e, t_quote q);

//pars_ass_helper2.c
int				find_equals(char *str);
void			free_clean(char **buf);

//pars_ass_helper3.c
int				expand_into(char *dst, char *src, t_variables *vars, int *i);
char			*fill_ret_question_helper(char *ret, 
					char *s1, int e, t_quote q);

//recursion.c
t_token			*val_pars_recursion(t_expression **result,
					t_token *token_list, char *path, t_variables *assign);
t_expression	*recursion(t_token **token_list,
					char *path, t_variables *assign, t_garbage *g);

// expansion_traversers.c
void			traverse_redirection(t_expression *cmd_parse,
					t_variables *assignments, int e);
void			traverse_arguments(t_expression *cmd_parse,
					t_variables *assignments, int e);
void			traverse_commands(t_expression *cmd_parse,
					t_variables *assignments, int e);

// trav_red_helper.c
void			expand_red_question(t_redirection *red_trav, int *i, int e);
void			trav_red_helper(int e, t_variables *assignments, 
					t_redirection *red_trav, int *i);

// exp_trav_helpers.c
void			expand_redirection(t_redirection *red_trav, 
					t_variables *ass_trav, int *i, int var_len);
void			repltoken(t_token **token_list, t_variables *ass_trav);
int				question_mark_check(char *str);
void			expand_question_mark(t_arg *arg_trav, int *i, int e);

// expansion_helpers.c
int				find_varname(char *s1);
void			quote_cleaner(t_expression *cmd_parse,
					t_variables *assignments, int e);
void			pars_exp_helper(t_token **token_list, t_variables *ass_trav);
void			seg_dup_helper(t_segment *seg, char **str, 
					t_variables *ass, int e);

//expansion_helpers2.c
void			repl_arg(int var_len, t_arg *arg_trav,
					t_variables *ass_trav, int i);
void			repl_empty_arg(int var_len, t_arg *arg_trav, int i);
void			expand_cmd_question(t_expression *cmds_trav, int e);

// expansion.c
void			replace_hdinput(t_redirection *red_trav,
					t_variables *ass_trav, int i);
void			expansion_checker(t_expression *cmd_parse,
					t_variables *assignments, int e);
void			expand_arguments(t_arg	*arg_trav, t_variables *ass_trav, 
					int *i, int var_len);
t_token			*parse_expansion(t_segment *seg, 
					t_token **token_list, t_variables *assignment);

char			*create_buf(char *str, int *i, int *j);

// extract_assignments.c
void			extract_assignments(t_expression *cmd_parse,
					t_variables **assignments, t_envs *b_env);
void			extractor(t_expression *cmd_parse, t_variables **assignment);
void			replace_exist_ass(t_expression *node,
					t_variables *assignmentlist, t_envs *env);

// ast_expansion_helpers.c
int				check_after(char *arg, int i, t_files *files, int j);
int				check_before(char *arg, int i, t_files *files);
void			check_for_ast(t_expression *cmd_parse);
void			remove_ast(t_arg **arg_trav);

// copy_env.c
char			*get_before_equal(char *str);
char			*get_after_equal(char *str);
t_env			*env_last(t_env *lst);

// copy_env2.c
void			append_env_list(t_env **result, t_env *new);
t_env			*copy_env(char **envp);
t_env			*init_env(char *str);
int				built_in(char *value);

// cope_env_to_alist.c
t_variables		*copy_env_to_alist(t_env *envp);

// ast_expansion.c
void			check_for_ast(t_expression *cmd_parse);
void			remove_ast(t_arg **arg_trav);

//ast_red_expansion.c
void			remove_ast_red(t_redirection **red_trav);
void			check_for_ast_red(t_expression *red);

// check_for_red_pipe.c
int				check_for_red_pipe(t_expression *parse_cmds);
void			handle_red_right_pipe(t_redirection *redirection,
					t_expression *parse_cmds);

// check_for_red.c
int				check_for_redirect(t_expression *parse_cmds);

// reset_fd.c
void			clean_all_heredoc(t_expression *parse_cmds);
void			clean_heredoc(t_expression *parse_cmds);
void			reset_fd(t_expression *parse_cmds);
int				execution2(t_expression *cmdparse, char **envp);

// check_red_type.c
int				check_red_type_r(t_expression *parse_cmds);
int				check_red_type_l(t_expression *parse_cmds);

//hd_helpers.c
void			prep_all_heredoc(t_expression *parse_cmds);
int				prep_heredoc(t_expression *parse_cmds);
void			fill_fd_file(t_redirection *red);

// builtin_helpers.c
int				built_in(char *value);
int				execute_built_in(t_expression *cmdparse,
					t_envs *b_envp, int exit, t_variables **assignmentlist);

// builtin_echo.c
int				execute_echo(t_expression *cmdparse, int exit);

// builtin.c
int				execute_export(t_expression *cmdparse, 
					t_env **envp, t_variables **assign);
int				execute_env(t_env **envp);
int				valid_identifier(char *str);

// builtin2.c
int				execute_pwd(void);
int				execute_unset(t_expression *cmdparse, 
					t_env **envp, t_variables **assign);
void			update_env_var(t_env **envp, char *keyword, 
					char *path, t_variables **assign);
int				change_dir(char *path);
char			*find_user_name(t_env **envp);

//builtin3.c
int				execute_exit(t_garbage *g, t_expression *node);
int				execute_cd(t_expression *cmdparse, 
					t_env **envp, t_variables **assign);

//builtin4.c
void			cd_helper(t_env **envp, char *oldpwd, t_variables **assign);
int				get_homepwd(t_env **envp);
void			update_assign2(char *name, char *value, t_variables **assign);

// execute_helpers.c
char			**copy_args(t_expression *cmd_parse);
char			*path_finder(t_expression *cmdparse);

// execute_rec.c
int				node_eval(t_expression *node, t_envs *b_env,
					t_variables **assignmentlist, int e);
int				priority(t_expression *node, t_variables **a_lst,
					t_envs *b_env, int prev_status);

// dup_a_list.c
t_variables		*dup_a_lst(t_variables *assignmentlist);
t_variables		*dup_assign(t_variables	*assign);
void			append_assign_lst(t_variables **ret, t_variables *new);
t_variables		*a_lst_last(t_variables *lst);

//dup_b_env.c
t_envs			*alloc_b_env(t_envs *b_env);
t_env			*dup_b_env(t_env *env);
t_env			*dup_env(t_env *lst);
void			append_env(t_env **ret, t_env *new);

//subshell_memory.c
t_env			*env_last(t_env *lst);
int				shell_subshell(t_expression *node, t_envs *b_env);

// execute_pipe.c
int				man_pipeline(t_expression *node,
					t_envs *b_env, int exit);
int				exec_in_pipe(t_expression *node,
					t_envs *b_env, int e, t_p *p);
int				exec_last_in_pipe(t_expression *node,
					t_envs *b_env, int e, t_p *p);
int				exec_pipe(t_expression *node, 
					t_envs *b_env, int exit, t_p *p);

// execute_pipe_helpers.c
void			file_thingy(t_expression *node);
void			file_thingy2(t_expression *node, t_p *p);

// execute.c
void			exec_pipe_cmd(t_expression *node, t_envs *b_env, int exit);

// execute2.c
int				execution(t_expression *cmdparse, t_envs *b_env);
void			child_process(char *path, char **args, t_envs *b_env);
int				convert_exit(int status);

// execute_helpers2.c
char			*path_slash_check(t_expression *node);
int				t_arg_length(t_arg *arg);
char			**env_to_array(t_env *env);

//freefile.c
void			free_array(char **str);
void			free_assignment(t_variables *ass);
void			free_args(t_arg *args);
void			free_red(t_redirection *red);
void			free_env(t_env *env);

//freefile2.c
void			free_tokens(t_token *token_list);
void			free_tree(t_expression *node);
void			free_rl_null(t_garbage *g);
void			free_iter(t_garbage *g, char *path);
void			free_files(t_files *files);

//freefile3.c
void			free_seg(t_segment *seg);
void			free_red2(t_redirection *red);
void			free_hd_child(t_redirection **red, t_garbage *g);

// history.c
void			history(char *input);

//check_files
int				check_files(char *arg, int i, t_files *files);
t_files			*retrieve_files(void);

//fd_closer.c
void			fd_closer(void);

//path_ok.c
void			path_ok(char *path, char **arg, t_envs *b_env);
void			free_pipe_stuff(char *path, char **args, t_envs *b_env);

//builtin_helpers2.c
void			unset_env(t_expression *cmdparse, t_env **envp);
void			unset_assign(t_expression *cmdparse, t_variables **assign);
void			export_assign(t_expression *cmdparse, t_variables **assign);
int				export_env(t_expression *cmdparse, t_env **envp);

//builtin_helpers3.c
int				update_env(t_expression *cmdparse, t_env **envp);
void			update_assign(t_expression *cmdparse, t_variables **assign);
void			print_export(t_env **env);

//signal.c
void			signal_set(void);
void			set_exit(t_garbage **g);
void			sig_hd_handler(int sig);
void			sig_exec_handler(int sig);

//update_shlvl
void			set_env(t_env *env, char *keyword, int lvl);
void			update_shlvl(t_env **env);

#endif