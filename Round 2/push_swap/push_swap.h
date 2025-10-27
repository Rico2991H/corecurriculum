/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:08:51 by rhoogend          #+#    #+#             */
/*   Updated: 2025/08/12 15:21:40 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_node 
{
	int				nb;
	int				pos; 
	struct s_node	*next;
}		t_list_node;

//void	push_swap(t_list_node **list);
int		count_list(t_list_node **stacka);
int		list_scan_top(t_list_node **stacka, int list_len, 
			int chunksize, int chunknb);
int		list_scan_bottom(t_list_node **stacka, int list_len, 
			int chunksize, int chunknb);
void	label_numbers(t_list_node **stacka);
void	rotate_inplace(t_list_node **list, int listlen, 
			int chunksize, int chunknb);
void	swap(t_list_node *stack);
void	push(t_list_node **stacka, t_list_node **stackb);
void	rotate(t_list_node **stack);
void	rev_rotate(t_list_node **stacka);
void	swapb(t_list_node *stack);
void	pushb(t_list_node **stacka, t_list_node **stackb);
void	rotateb(t_list_node **stack);
void	rev_rotateb(t_list_node **stacka);
void	remove_node(t_list_node **head);
int		append_node(t_list_node **head, int new_nbr, int new_pos);
int		prepend_node(t_list_node **head, int new_nbr, int new_pos);
void	sort3(t_list_node **list);
void	sort(t_list_node **list, int numchunks, int listlen, int chunksize);
void	stupid_extra_fun(t_list_node **listb, int rev_rotations);
int		ft_atoi(const char *nptr, int argc, char **argv);
int		int_check(int argc, char **argv);
int		doublenum_check(int argcount, int argc, char **argv);
int		rotate_highest(t_list_node **stacka, int listlen);
void	rotate_lowest(t_list_node **stacka);
int		is_sorted(t_list_node *lista);
void	free_list(t_list_node *list);
void	sort5(t_list_node **list);
char	**ft_split(const char *s, char c);
void	free_split(char **arr);

#endif
