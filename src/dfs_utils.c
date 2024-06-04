/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:22 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/04 18:53:01 by jtakahas         ###   ########.fr       */
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

bool	is_target(t_game *game,
			t_point player,
			char target,
			int *can_get_coin,
			t_stack *stack)
{
	if (game->map.map_str[player.y][player.x] == target)
	{
		printf("target: %c\n", target);
		printf("can_get_coin: %d\n", *can_get_coin);
		if ((*can_get_coin) == 0 || target == EXIT)
		{
			free_stack(stack);
			return (true);
		}
		(*can_get_coin)--;
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
