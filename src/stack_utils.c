/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 17:40:07 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/08 17:40:08 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	push(t_stack *stack, t_point point)
{
	t_node	*node;

	node = init_node(point);
	if (node == NULL)
		error_and_exit("Malloc error", NULL, NULL);
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
