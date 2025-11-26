/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:35:22 by dmungunt          #+#    #+#             */
/*   Updated: 2025/11/26 16:08:02 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	execute_export(t_expression *cmdparse, t_env **envp)
{
	t_env	*last;
	t_env	*new;

	last = env_last(*envp);
	new = init_env(cmdparse->args->arg);
	append_env_list(envp, new);
	printf("it_worked\n");
	return (0);
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

int	 execute_echo(t_expression *cmdparse)
{
	t_arg	*tmp;

	if (!cmdparse || !cmdparse->args)
	{
		printf("\n");
		return (0);
	}
	tmp = cmdparse->args;
	if (ft_strncmp(tmp->arg, "-n", 2) && ft_strlen(tmp->arg) == 2)
	{
		tmp = tmp->next;
		while (tmp)
		{
			printf("%s", tmp->arg);
			tmp = tmp->next;
		}			
	}
	else
	{
		tmp = cmdparse->args;
		while (tmp)
		{
			printf("%s ", tmp->arg);
			tmp = tmp->next;
		}
		printf("\n");
	}	
	return (0);
}

void	update_env_var(t_env **envp, char *keyword, char *path)
{
	t_env	*tmp;

	tmp = *envp;
	while ((tmp))
	{
		if (ft_strncmp(tmp->before_equal, keyword, ft_strlen(keyword)) == 0)
		{
			free(tmp->after_equal);
			tmp->after_equal = ft_strdup(path);
		}

		tmp = tmp->next;
	}
}

void	change_dir(char *path)
{
	if (chdir(path))
	{
		perror("chdir :");
		exit(1);
	}
}

int	execute_cd(t_expression *cmdparse, t_env **envp)
{
	char	*oldpwd;
	char	*newpwd;
	
	oldpwd = getcwd(NULL, 0);
	if (cmdparse->args)
		change_dir(cmdparse->args->arg);
	else
		change_dir("/home/dmungunt");
	newpwd = getcwd(NULL, 0);
	update_env_var(envp, "OLDPWD=", oldpwd);
	update_env_var(envp, "PWD=", newpwd);
	free(oldpwd);
	free(newpwd);
	return (0);
}

int	execute_pwd()
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	execute_unset(t_expression *cmdparse, t_env **envp)
{
	t_env	*tmp;
	t_env	*prev;
	
	tmp = *envp;
	while (tmp)
	{
		if (ft_strncmp(cmdparse->args->arg, tmp->before_equal, ft_strlen(cmdparse->args->arg)) == 0 
			&& tmp->before_equal[ft_strlen(cmdparse->args->arg)] == '\0')
		{
			if (prev == NULL)
				*envp = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->after_equal);
			free(tmp->before_equal);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

int	execute_built_in(t_expression *cmdparse, t_env **envp)
{
	int	status;
	
	status = 0;
	//printf("the value in cmdparse: %s\n", cmdparse->value);
	if (ft_strncmp("echo", cmdparse->value, 4) == 0)
	{
		status = execute_echo(cmdparse);
	}
	else if (ft_strncmp("cd", cmdparse->value, 2) == 0)
	{
		status = execute_cd(cmdparse, envp);
	}
	else if (ft_strncmp("pwd", cmdparse->value, 3) == 0)
		status = execute_pwd();
	else if (ft_strncmp("export", cmdparse->value, 6) == 0)
	{
		status = execute_export(cmdparse, envp);
	}
	else if (ft_strncmp("unset", cmdparse->value, 5) == 0)
	{
		status = execute_unset(cmdparse, envp);
	}
	else if (ft_strncmp("env", cmdparse->value, 3) == 0)
	{
		status = execute_env(envp);
	}
	else if (ft_strncmp("exit", cmdparse->value, 4) == 0)
	{
		//status = execute_exit();
	}
	reset_fd(cmdparse);
	return (status);
}

char	*path_finder(t_expression *cmdparse)
{
	char	*slashed_cmd;
	char	*path_cmd;
	int		i;
	
	i = 0;
	slashed_cmd = ft_strjoin("/", cmdparse->value);
	while(cmdparse->split_paths[++i])
	{
		path_cmd = ft_strjoin(cmdparse->split_paths[i], slashed_cmd);
		if(!path_cmd)
		{
			perror("Error: command path");
			return(0);
		}
		if(access(path_cmd, F_OK) == 0)
		{
			printf("this is path _cmd:  %s \n", path_cmd);
			free(slashed_cmd);
			return (path_cmd);
		}
	}
	free(slashed_cmd);
	return(NULL);
}

int	built_in(char *value)
{
	if (ft_strncmp("echo", value, 4) == 0)
		return (1);
	else if (ft_strncmp("cd", value, 2) == 0)
		return (1);
	else if (ft_strncmp("pwd", value, 3) == 0)
		return (1);
	else if (ft_strncmp("export", value, 6) == 0)
		return (1);
	else if (ft_strncmp("unset", value, 5) == 0)
		return (1);
	else if (ft_strncmp("env", value, 3) == 0)
		return (1);
	else if (ft_strncmp("exit", value, 4) == 0)
		return (1);
	return (0);
}

int	t_arg_length(t_arg *arg)
{
	int	i;

	i = 0;
	while(arg)
	{
		i++;
		arg = arg->next;
	}
	return (i);
}

char	**copy_args(t_expression *cmd_parse)
{
	char	**execve_args;
	int		i;

	if (!cmd_parse->args)
		return (NULL);
	i = t_arg_length(cmd_parse->args);
	i++;
	execve_args = malloc(sizeof(char *) * (i + 1));
	if (!execve_args)
	{
		return (NULL);
	}
	i = 0;
	execve_args[i] = cmd_parse->value;
	i++;
	while(cmd_parse->args != NULL)
	{
		execve_args[i] = cmd_parse->args->arg;
		i++;
		cmd_parse->args = cmd_parse->args->next;
	}
	execve_args[i] = NULL;
	return (execve_args);
}

void	child_process(char **envp, char *path, char **args)
{
	printf("I am in the exectution proces\n");
	printf("envp = %s\n path = %s\n args = %s\n", *envp, path, *args);
	if (execve(path, args, envp) == -1)
		perror("execve failed:");
	return;
}

int	execution(t_expression *cmdparse, char **envp)
{
	char	*path;
	char	**args;
	int status;
	pid_t	pid;
	
	status = 0;
	path = path_finder(cmdparse);
	args = copy_args(cmdparse);
	if (!path)
		return (status);
	pid = fork();
	if (pid == -1)
	{
		perror("fork unsuccesfull");
		return(-1);
	}
	if (pid == 0)
	{
		child_process(envp, path, args); // we cant return, it needs to exit in order to return to the parent.
		exit(0); 
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		printf("We all have returned\n");
		free(path);
	}
	return (status);
}

int	node_eval(t_expression *node, t_env **env, t_variables **assignmentlist, char **r_envp)
{
	if (!node)
		return (0);
	check_for_redirect(node); 
	if (node->Type == NODE_COMMAND)
	{
		if (built_in(node->value))
			return (execute_built_in(node, env));
		else
			return (execution(node, r_envp));
	}
	if (node->Type == NODE_ASSIGNMENT)
	{
		extractor(node, assignmentlist);
		expansion_checker(node, *assignmentlist);
		reset_fd(node);
		return (0);
	}
	return (0);
}


int	priority(t_expression *node, t_env **env, t_variables **assignmentlist, char **r_envp)
{	
	int	left_status;
	//int	right_status;
	if (!node)
		return (0);
	printf("In priority\n");
	
	if (!node)
		return (0);
	if (node->Type == NODE_PIPE)
	{
		printf("run exec_pipe\n");
		//return (exec_pipe(node, env, assignmentlist, r_envp));
	}
	if (node->Type == NODE_COMMAND || node->Type == NODE_ASSIGNMENT)
	{
		printf("executing cmd: %s %s\n", node->value, node->args->arg);
		return (node_eval(node, env, assignmentlist, r_envp));
	}
	if (node->Type == NODE_AND)
	{
		printf("enters NODE_AND\n");
		left_status = priority(node->left, env, assignmentlist, r_envp);
		if (left_status == 0)
		{
			return (priority(node->right, env, assignmentlist, r_envp));
		}
		return (left_status);
	}
	if (node->Type == NODE_OR)
	{
		printf("enters NODE_OR\n");
		left_status = priority(node->left, env, assignmentlist, r_envp);
		if (left_status != 0)
		{
			return (priority(node->right, env, assignmentlist, r_envp));
		}
		else
			return (priority(node->right->right, env, assignmentlist, r_envp));
		return (left_status);
	}
	return (0);
}

/*int	execute_or(t_expression **cmdparse, t_env **envp, t_variables **assignments, char **r_envp)
{
	int	status;

	status = 0;
	if ((*cmdparse)->left->Type == NODE_COMMAND)
	{
		if (built_in((*cmdparse)->left->value))
		{
			printf("executing in or\n");
			status = execute_built_in((*cmdparse)->left, envp);
			if (status == 1)
			{
				(*cmdparse) = (*cmdparse)->right;
				if ((*cmdparse)->Type == NODE_AND || (*cmdparse)->Type == NODE_OR)
				{
					if((*cmdparse)->left->Type == NODE_COMMAND)
						status = execute_built_in((*cmdparse)->left, envp);
					if((*cmdparse)->left->Type == NODE_ASSIGNMENT)
					{
						printf("EXTRACTING BABY\n");
						extractor((*cmdparse)->left, assignments);
					}
				}
				else
				{
					if((*cmdparse)->left->Type == NODE_COMMAND)
						status = execute_built_in((*cmdparse)->left, envp);
					if((*cmdparse)->left->Type == NODE_ASSIGNMENT)
					{
						extractor((*cmdparse)->left, assignments);
						expansion_checker(*cmdparse, *assignments);
					}
				}
			}
			else
			{
				(*cmdparse) = (*cmdparse)->right;
				if ((*cmdparse)->Type == NODE_COMMAND || (*cmdparse)->Type == NODE_AND)
					(*cmdparse) = (*cmdparse)->right;
			}
		}
		else
		{
			status = execution((*cmdparse)->left, r_envp);
			if (status != 0)
			{
				(*cmdparse) = (*cmdparse)->right;
				if (built_in((*cmdparse)->left->value))
					execute_built_in((*cmdparse)->left, envp);
				else
					status = execution((*cmdparse)->left,r_envp);
			}
		}
	}
	else if ((*cmdparse)->left->Type == NODE_ASSIGNMENT)
	{
		printf("extract in or\n");
		extractor((*cmdparse)->left, assignments);
		expansion_checker(*cmdparse, *assignments);
		(*cmdparse) = (*cmdparse)->right;
		if ((*cmdparse)->Type == NODE_AND || (*cmdparse)->Type == NODE_OR)
		{
			if((*cmdparse)->left->Type == NODE_COMMAND)
				status = execute_built_in((*cmdparse)->left, envp);
			if((*cmdparse)->left->Type == NODE_ASSIGNMENT)
			{
				extractor((*cmdparse)->left, assignments);
				expansion_checker(*cmdparse, *assignments);
			}
		}
		else
		{
			printf("move right once more\n");
			if ((*cmdparse)->Type == NODE_COMMAND || (*cmdparse)->Type == NODE_AND)
				(*cmdparse) = (*cmdparse)->right;
		}
	}
	return (status);
}

int	execute_and(t_expression **cmdparse, t_env **envp, t_variables **assignments, char **r_envp)
{
	int	status;

	status = 1;
	if ((*cmdparse)->left->Type == NODE_COMMAND)
	{
		if (built_in((*cmdparse)->left->value))
		{
			status = execute_built_in((*cmdparse)->left, envp);
			if (status == 0)
			{
				(*cmdparse) = (*cmdparse)->right;
				if ((*cmdparse)->Type == NODE_AND || (*cmdparse)->Type == NODE_OR)
				{
					if((*cmdparse)->left->Type == NODE_COMMAND)
						status = execute_built_in((*cmdparse)->left, envp);
					if((*cmdparse)->left->Type == NODE_ASSIGNMENT)
					{
						extractor((*cmdparse)->left, assignments);
						expansion_checker(*cmdparse, *assignments);
					}
				}
				else if ((*cmdparse)->Type == NODE_COMMAND)
				{
					status = execute_built_in((*cmdparse), envp);
					(*cmdparse) = (*cmdparse)->right;
				}
				else
				{
					if((*cmdparse)->left->Type == NODE_COMMAND)
						status = execute_built_in((*cmdparse), envp);
					if((*cmdparse)->left->Type == NODE_ASSIGNMENT)
						extractor((*cmdparse)->left, assignments);
				}

			}
		}
		else
		{
			status = execution((*cmdparse)->left, r_envp);
			if (status != 0)
			{
				(*cmdparse) = (*cmdparse)->right;
				if (built_in((*cmdparse)->left->value))
					execute_built_in((*cmdparse)->left, envp);
				else
					status = execution((*cmdparse)->left, r_envp);
			}
		}
	}
	else if ((*cmdparse)->left->Type == NODE_ASSIGNMENT)
	{
		extractor((*cmdparse)->left, assignments);
		expansion_checker(*cmdparse, *assignments);
		(*cmdparse) = (*cmdparse)->right;
		if ((*cmdparse)->Type == NODE_AND || (*cmdparse)->Type == NODE_OR)
			{
				if((*cmdparse)->left->Type == NODE_COMMAND)
					status = execute_built_in((*cmdparse)->left, envp);
				if((*cmdparse)->left->Type == NODE_ASSIGNMENT)
				{
					extractor((*cmdparse)->left, assignments);
					expansion_checker(*cmdparse, *assignments);
				}
			}
		status = 0;
	}
	return(status);
}

int	execute_cmd(t_expression **cmdparse, char **r_envp, t_env **envp)
{
	int	status;
	
	status = 0;
	if (built_in((*cmdparse)->value))
	{
		printf("enters built_in if statement\n");
		status = execute_built_in(*cmdparse, envp);
		(*cmdparse) = (*cmdparse)->right;
	}
	else
	{
		status = execution(*cmdparse, r_envp);
		(*cmdparse) = (*cmdparse)->right;
	}
	return (status);
}

void	priority(t_expression *cmdparse, t_env **envp, int exit_status, t_variables **assignments, char **r_envp)
{
	if (!cmdparse)
		return ;
	if (cmdparse->Type == NODE_AND && (exit_status == 0 || exit_status == 2))
	{
		printf("execute and\n");
		exit_status = execute_and(&cmdparse, envp, assignments, r_envp);
		priority(cmdparse, envp, exit_status, assignments, r_envp);
	}
	else if (cmdparse->Type == NODE_OR && (exit_status == 1 || exit_status == 2))
	{
		printf("execute or\n");
		exit_status = execute_or(&cmdparse, envp, assignments, r_envp);
		printf("exited with %d\n", exit_status);
		priority(cmdparse, envp, exit_status, assignments, r_envp);
		if (exit_status == 0 && cmdparse->Type == NODE_OR)
		{
			cmdparse = cmdparse->right;
			printf("SEEEEEEE: %s\n", cmdparse->value);
		}
	}
	else if (cmdparse->Type == NODE_PIPE)
	{
		// execute pipe or pipes ;
	}
	else if (cmdparse->Type == NODE_ASSIGNMENT)
	{
		printf("extracting\n");
		extractor(cmdparse, assignments);
		expansion_checker(cmdparse, *assignments);
		cmdparse = cmdparse->right;
		if (!cmdparse)
			return ;
		priority(cmdparse, envp, exit_status, assignments, r_envp);
	}
	else  if (cmdparse->Type == NODE_COMMAND && exit_status == 2)
	{
		printf("exexuting\n");
		if (built_in(cmdparse->value))
			exit_status = execute_built_in(cmdparse, envp);
		else
			exit_status = execute_cmd(&cmdparse, r_envp, envp); 
	}
	else
		cmdparse = cmdparse->right;
	//priority(cmdparse, envp, exit_status, assignments, r_envp);
}*/
