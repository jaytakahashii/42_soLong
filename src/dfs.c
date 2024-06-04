/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:04 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/04 18:52:13 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	**init_direction(void)
{
	int	**direction;
	int	i;

	direction = (int **)malloc(sizeof(int *) * 4);
	if (direction == NULL)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		direction[i] = (int *)malloc(sizeof(int) * 2);
		if (direction[i] == NULL)
			return (NULL);
		direction = basic_vector(i, direction);
		i++;
	}
	return (direction);
}

void	register_next(t_game *game, t_stack *stack, int **visited, t_point next)
{
	t_node	*node;
	t_point	tmp;

	tmp = next;
	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		error_and_exit("Memory allocation error",
			"failed to allocate memory",
			game);
	node->point = tmp;
	node->next = NULL;
	push(stack, node);
	visited[next.y][next.x] = 1;
}

int	register_direction(t_game *game,
		t_stack *stack,
		int **visited,
		t_point current,
		char target)
{
	t_point	next;
	int		**direction;
	int		i;

	i = 0;
	direction = init_direction();
	while (i < 4)
	{
		next = (t_point){current.x + direction[i][0],
			current.y + direction[i][1]};
		if (is_valid_point(game, next, target) && !visited[next.y][next.x])
		{
			register_next(game, stack, visited, next);
			break ;
		}
		i++;
	}
	free(direction);
	return (i);
}

int	**init_visited(t_game *game)
{
	int	**visited;
	int	i;
	int	j;

	visited = (int **)malloc(sizeof(int *) * game->map.height);
	if (visited == NULL)
		error_and_exit("Memory allocation error", NULL, game);
	i = 0;
	while (i < game->map.height)
	{
		visited[i] = (int *)malloc(sizeof(int) * game->map.width);
		if (visited[i] == NULL)
			error_and_exit("Memory allocation error", NULL, game);
		j = 0;
		while (j < game->map.width)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	return (visited);
}

bool	dfs(t_game *game, t_point player, char target, int can_get_coin)
{
	t_stack	stack;
	t_node	*node;
	t_point	current;
	int		**visited;
	int		i;

	visited = init_visited(game);
	stack.top = NULL;
	node = init_node(player);
	push(&stack, node);
	visited[player.y][player.x] = 1;
	while (stack.top != NULL)
	{
		current = stack.top->point;
		printf("current: %d, %d\n", current.x, current.y);
		if (is_target(game, current, target, &can_get_coin, &stack))
			return (true);
		i = register_direction(game, &stack, visited, current, target);
		if (i == 4)
		{
			node = pop(&stack);
			free(node);
		}
	}
	free_stack(&stack);
	return (false);
}
