/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:47:30 by rhoogend          #+#    #+#             */
/*   Updated: 2025/10/14 17:07:36 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_cmd
{
    char    **path;
    char    **tokens;
	int		fd;
}   t_cmd;

size_t	ft_strlen(const char *string)
{
	size_t	i;

	i = 0;
	while (string[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ptr;
	size_t	i;
	size_t	j;

	j = ft_strlen((char *)s1);
	i = 0;
	len = j + ft_strlen((char *)s2);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < j)
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (j != len)
	{
		ptr[j] = s2[i];
		j++;
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

static int	word_count(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*alloc_word(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = s[start];
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**fill_words(char **arr, const char *s, char c)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			arr[j] = alloc_word(s, start, i);
			if (!arr[j])
				return (NULL);
			j++;
		}
		else
			i++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	int		count;

	if (!s)
		return (NULL);
	count = word_count(s, c);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	return (fill_words(arr, s, c));
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*ptr;

	i = 0;
	len = 0;
	while (s[len] != '\0')
	{
		len++;
	}
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (s[i] != '\0')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i ;

	i = 0;
	while (i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		if (s1[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return (0);
}

char	*getpath(char **envp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (envp [i] && ft_strncmp(envp[i], "PATH", 4))
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_strdup(&envp[i][j + 5]));
}
static void	prep_proces(char *arg, char *path, t_cmd *heredoccmd)
{
	heredoccmd->path = ft_split(path, ':');
	if (!heredoccmd->path)
	{
		perror("split_paths failed");
		free(path);
	} 
	heredoccmd->tokens = ft_split(arg, ' ');
	if (!heredoccmd->tokens)
	{
		perror("split_args failed");
		free(path);
		//free_split_paths(heredoccmd);
		exit(1);
	}

}
void	find_exec_path(t_cmd *heredoccmd, char *slash_cmd, char **envp)
{
	int			i;
	char		*j_path;
	int			flag;
	char *argv_exec[2];

	argv_exec[0] = heredoccmd->tokens[0];  // the command itself
	argv_exec[1] = NULL;   
	i = -1;
	flag = 0;
	while (heredoccmd->path[++i])
	{
		j_path = ft_strjoin(heredoccmd->path[i], slash_cmd);
		if (!j_path)
		{
			perror("joining paths failed\n");
			return ;
		}
		if ((access(j_path, F_OK) == 0) && (access(j_path, X_OK) == 0))
		{
			flag = 1;
			if (execve(j_path, argv_exec, envp) == -1)
				perror("execution fail\n");
		}
		free(j_path);
	}
	if (flag == 0)
		perror("path not found");
}

void	exec_cmd(t_cmd *heredoccmd, char **envp)
{
	char	*slash_cmd;

	slash_cmd = ft_strjoin("/", heredoccmd->tokens[0]);
	find_exec_path(heredoccmd, slash_cmd, envp);
	//child_free_and_exit(proces);
}

void    heredoc(char *arg, char **envp)
{
    t_cmd   *heredoccmd = malloc(sizeof(t_cmd));
    char    *path = getpath(envp);
    int     pid;
    int     fd[2];
    
    prep_proces(arg, path, heredoccmd);
    pipe(fd);
    pid = fork();
	if (pid == -1)
	{
		perror("fork unsuccesfull");
		exit(1);
	}
    else if (pid == 0)
    {
        char *docarg;
        close(fd[0]);
        while((docarg = readline("heredoc> ")) != NULL && ft_strncmp(heredoccmd->tokens[2], docarg, ft_strlen(docarg)))
        {	        
			add_history(docarg); //separate history
            write(fd[1], &docarg[0], ft_strlen(docarg));
			write(fd[1], "\n", 1);
			free(docarg);
        }
		close(fd[1]);
		exit(0);
    }
    else
    {
        int     status;
		close(fd[1]);
        waitpid(pid, &status, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exec_cmd(heredoccmd, envp);
		
    }
}

int main(int argc, char *argv[], char **envp)
{
    (void)argc;
    (void)**argv;
    char *arg;
    int i = 1;

    while((arg = readline("Minishell ")) != NULL)
    {
        add_history(arg);
        while (arg[i] && ft_strncmp(&arg[i], "<<", 2))
            i++;
        if (arg[i] && !ft_strncmp(&arg[i], "<<", 2))
        {
            heredoc(arg, envp);
            wait(NULL);
        }
        i = 0;
    }
    rl_clear_history();
}