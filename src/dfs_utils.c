/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:22 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/08 12:54:07 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_valid_point(t_game *game, t_point point, char target)
{
	if (point.x < 1 || point.y < 1
		|| point.x >= game->map.width - 1
		|| point.y >= game->map.height - 1)
		return (false);
	if (target == COLLECTIBLE)
	{
		if (game->map.map_str[point.y][point.x] == WALL
			|| game->map.map_str[point.y][point.x] == EXIT)
			return (false);
	}
	else if (target == EXIT)
	{
		if (game->map.map_str[point.y][point.x] == WALL)
			return (false);
	}
	return (true);
}

bool	is_target(t_game *game, char target, t_dfs *dfs)
{
	if (game->map.map_str[dfs->current.y][dfs->current.x] == target)
	{
		if (target == COLLECTIBLE)
			game->map.map_str[dfs->current.y][dfs->current.x] = CAN_GET_COIN;
		return (true);
	}
	return (false);
}

int	**basic_vector(int i, int **direction)
{
	if (i == 0)
	{
		direction[i][0] = 1;
		direction[i][1] = 0;
	}
	else if (i == 1)
	{
		direction[i][0] = 0;
		direction[i][1] = 1;
	}
	else if (i == 2)
	{
		direction[i][0] = -1;
		direction[i][1] = 0;
	}
	else if (i == 3)
	{
		direction[i][0] = 0;
		direction[i][1] = -1;
	}
	return (direction);
}

void	free_int_map(int **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_stack(t_stack *stack)
{
	t_node	*node;
	t_node	*tmp;

	node = stack->top;
	while (node)
	{
		tmp = node->next;
		free(node);
		node = tmp;
	}
	stack->top = NULL;
}

void	free_dfs(t_dfs *dfs, int map_height)
{
	if (dfs->visited)
		free_int_map(dfs->visited, map_height);
	if (dfs->direction)
		free_int_map(dfs->direction, 4);
	if (dfs->stack.top)
		free_stack(&dfs->stack);
}
