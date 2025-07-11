/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortbproto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 08:34:32 by rhoogend          #+#    #+#             */
/*   Updated: 2025/07/11 08:34:45 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*void	sortb(list_node **lista, list_node **listb )
{	
	list_node	*temp;
	int	rotations;
	int	highest;
	int	listlen;
	int	lowest;
	
	rotations = 0;
	highest = 0;
	lowest = 0;
	temp = *listb;
	if (!*lista)
		return;
	if ((*listb)->next == NULL)
	{
		push(lista, listb);
		write(1,"pb\n",4);
		if ((*listb)->pos < (*listb)->next->pos)
		{
			swap(*listb);
			write(1,"sb\n",4);
		}
		return;
	}
	listlen = count_list(listb);
	lowest = scan_list(listb);
	if ((*lista)->pos < lowest)
	{
		push(lista,listb);
		write(1,"pb\n",4);
		rotate(listb);

		return;
	}
	while (temp && temp->next && (*lista)->pos < temp->pos)
	{
		rotations++;
		if ((*lista)->pos > temp->next->pos)
			break;
		temp = temp->next;
	}
	while(rotations != 0)
	{
		rotate(listb);
		write(1,"rb\n",4);
		rotations--;
		highest++;
	}
	if (*lista)
	{
		push(lista, listb);
		write(1,"pb\n",4);
	}
	while(highest != 0)
	{
		rev_rotate(listb);
		write(1,"rrb\n",5);
		highest--;
	}
}*/
