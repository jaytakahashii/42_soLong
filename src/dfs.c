/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:04 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/09 12:30:17 by jay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	**init_direction(void)
{
	int	**direction;
	int	i;
	int	j;

	direction = malloc(sizeof(int *) * 4);
	if (direction == NULL)
		return (NULL);
	i = -1;
	while (++i < 4)
	{
		direction[i] = (int *)malloc(sizeof(int) * 2);
		if (direction[i] == NULL)
		{
			j = -1;
			while (++j < i)
				free(direction[j]);
			free(direction);
			return (NULL);
		}
		direction = basic_vector(i, direction);
	}
	return (direction);
}

bool	register_next(t_point next, t_dfs *dfs)
{
	if (!push(&dfs->stack, next))
		return (false);
	dfs->visited[next.y][next.x] = 1;
	return (true);
}

int	register_direction(t_game *game, char target, t_dfs *dfs)
{
	t_point	next;
	int		i;

	dfs->direction = init_direction();
	if (!dfs->direction)
		return (-1);
	i = -1;
	while (++i < 4)
	{
		next = (t_point){dfs->current.x + dfs->direction[i][0],
			dfs->current.y + dfs->direction[i][1]};
		if (is_valid_point(game, next, target)
			&& !dfs->visited[next.y][next.x])
		{
			if (!register_next(next, dfs))
				return (-1);
			break ;
		}
	}
	free_int_matrix(dfs->direction, 4);
	dfs->direction = NULL;
	return (i);
}

int	**init_visited(t_game *game, t_point player)
{
	int	**visited;
	int	i;
	int	j;

	visited = (int **)malloc(sizeof(int *) * game->map.height);
	if (!visited)
		return (NULL);
	i = -1;
	while (++i < game->map.height)
	{
		visited[i] = (int *)malloc(sizeof(int) * game->map.width);
		if (visited[i] == NULL)
		{
			while (i-- > 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		j = -1;
		while (++j < game->map.width)
			visited[i][j] = 0;
	}
	visited[player.y][player.x] = 1;
	return (visited);
}

bool	dfs(t_game *game, t_point player, char target)
{
	t_dfs	dfs;
	int		i;
	bool	found;

	dfs_init(&dfs);
	i = 0;
	found = false;
	dfs.visited = init_visited(game, player);
	if (!dfs.visited || !push(&dfs.stack, player))
		i = -1;
	while (dfs.stack.top && i != -1)
	{
		dfs.current = dfs.stack.top->point;
		if (is_target(game, target, &dfs))
		{
			found = true;
			break ;
		}
		i = register_direction(game, target, &dfs);
		if (i == 4)
			free(pop(&dfs.stack));
	}
	free_dfs(&dfs, game);
	return (found);
}
