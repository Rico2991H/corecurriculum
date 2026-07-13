/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:02:10 by rhoogend          #+#    #+#             */
/*   Updated: 2026/04/10 17:12:09 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10 
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_buf
{
	char			*str_buf;
	struct s_buf	*next;
}			t_buf;

int		check_n(t_buf **list, int *i);
int		newline(char *buf);
int		len_line(t_buf *list);
char	*get_next_line(int fd);
void	remove_list(t_buf **list);
void	*add_node(t_buf **list, char *line);

#endif
