/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhoogend <rhoogend@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:08:01 by rhoogend          #+#    #+#             */
/*   Updated: 2025/06/26 17:45:14 by rhoogend         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* these are all the unique commands swap, push, rotate and reverse rotate they can be applied to both stacks sometimes they have to be applied to both stacks */
#include <stdio.h>
#include <stdlib.h>

void	swap (int *stack, int len)
{
	int	temp;
	int	i; 
	i = 0;
	temp = stack[i];
	stack[i] = stack[len - 1];
	stack[len - 1] = temp;
}
void	push(int *stack1, int *stack2, int len) 
{
	int	i;
	i = 0;
	while(i < len)
	{	
		stack2[i + 1] = stack2[i]; //6 . . . . . // . 6 . . . . // . . 6 . .
			i++;
	}
	if (stack2[i + 1] != len)
		stack2[i + 1] = stack2[i];
	stack2[i] = stack1[i];
	/*while(stack1[i])
	{
		stack1[i] = stack1[i + 1];
		i++;
	}*/
}
void	rotate(int *stack, int len)
{
	int	temp;
	int	i;
	i = 0;

	temp = stack[len - 1];
	len--;
	while(stack[i])                   
	{
		stack[len] = stack[len - 1];  
		i++; 
		len--;
		if (len == 0)
		{
			stack[len] = temp;
			break;
		}
	}
	i = 0; 	
}


void	rev_rotate(int	*stack, int len)
{
	int	temp;
	int	i;
	i = 0;
	temp = stack[i];
	while(stack[i])
	{
		stack[i] = stack[i + 1]; 
		i++;
		if (i == len - 1) 
		{
			stack[i] = temp;
			break;
		}
	}
}


int	main(int argc,char **argv)
{
	if (argc <= 1 )
	{
		return (1);
	}
	int	j = 0;
	int	stacka[argc - 1];
	int	i = 1;
	while (i < argc)
	{
		stacka[i - 1] = atoi(argv[i]);
		//printf("%d", stacka[i]); 
		i++;
		j++;
	}
	stacka[i - 1] = '\0'; 
	swap(stacka, argc - 1); 
	i = 0; 
	while(stacka[i])
	{
		printf("%d", stacka[i]); 
		i++;
	}
	printf("\n");
	int	stackb[argc - 1];
	stackb[argc - 1] = '\0';
	push(stacka, stackb, argc - 1);
	printf("%d\n", *stackb);
	push(stacka, stackb, argc - 1);
	i = 0;
	while(stackb[i])
	{
		printf("%d", stackb[i]);
		i++;
	}
	printf("%d\n", *stackb);	
	rotate(stacka, (argc - 1));
	i = 0;
	while(stacka[i])
	{
		printf("%d", stacka[i]);
		i++;
	}
	printf("\n");
	rev_rotate(stacka, argc - 1);
	i = 0;
	while(stacka[i])
	{
		printf("%d", stacka[i]);
		i++;
	}	
	return (0);
}
