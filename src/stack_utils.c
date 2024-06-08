/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:54 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/08 16:36:14 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	push(t_stack *stack, t_node *node)
{
	if (stack->top == NULL)
	{
		stack->top = node;
		return ;
	}
	node->next = stack->top;
	stack->top = node;
}

t_node	*pop(t_stack *stack)
{
	t_node	*node;

	if (stack->top == NULL)
		return (NULL);
	node = stack->top;
	stack->top = stack->top->next;
	return (node);
}

t_node	*init_node(t_point point)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->point = point;
	node->next = NULL;
	return (node);
}

void	free_stack(t_stack *stack)
{
	t_node	*node;

	while (stack->top)
	{
		node = pop(stack);
		free(node);
	}
}
