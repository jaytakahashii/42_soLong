/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:57 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/08 13:39:34 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	strlen_double_ptr(char **str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	add_player(t_game *game, int x, int y, char map_c)
{
	if (map_c == PLAYER)
	{
		game->player.point.x = x;
		game->player.point.y = y;
		game->map.player_count++;
	}
	if (game->map.player_count > 1)
	{
		free_map(game->map.map_str);
		error_and_exit("Invalid map", "map must contain only one player", NULL);
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
