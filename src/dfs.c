/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:04 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/05 02:50:22 by jay              ###   ########.fr       */
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

void	register_next(t_game *game, t_point next, t_dfs *dfs)
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
	push(&dfs->stack, node);
	dfs->visited[next.y][next.x] = 1;
}

int	register_direction(t_game *game, char target, t_dfs *dfs)
{
	t_point	next;
	int		i;

	i = 0;
	dfs->direction = init_direction();
	while (i < 4)
	{
		next = (t_point){dfs->current.x + dfs->direction[i][0],
			dfs->current.y + dfs->direction[i][1]};
		if (is_valid_point(game, next, target) && !dfs->visited[next.y][next.x])
		{
			register_next(game, next, dfs);
			break ;
		}
		i++;
	}
	free(dfs->direction);
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

bool	dfs(t_game *game, t_point player, char target)
{
	t_dfs	dfs;
	t_node	*node;
	int		i;

	dfs.visited = init_visited(game);
	dfs.stack.top = NULL;
	node = init_node(player);
	push(&dfs.stack, node);
	dfs.visited[player.y][player.x] = 1;
	while (dfs.stack.top)
	{
		dfs.current = dfs.stack.top->point;
		if (is_target(game, target, &dfs))
			return (true);
		i = register_direction(game, target, &dfs);
		if (i == 4)
		{
			node = pop(&dfs.stack);
			free(node);
		}
	}
	free_stack(&dfs.stack);
	return (false);
}
