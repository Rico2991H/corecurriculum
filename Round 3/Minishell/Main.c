/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:39:49 by rhoogend          #+#    #+#             */
/*   Updated: 2025/09/23 11:37:33 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

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
        {
            i++;
        }
        if (arg[i] && !ft_strncmp(&arg[i], "<<", 2))
            heredoc(arg, envp);
        i = 0;
    }
    rl_clear_history();
}
