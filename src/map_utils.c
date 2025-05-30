/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:41 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/08 16:22:30 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_rectangular(int first_line_len, int line_len, t_game *game)
{
	if (first_line_len != line_len)
		error_and_exit("Invalid map",
			"map width size is not rectangular", game);
}

void	check_height(int height, t_game *game)
{
	if (height < 3)
		error_and_exit("Invalid map",
			"map height size must be 2 or more", game);
	if (height > MAX_HEIGHT_IMAGE)
		error_and_exit("Invalid map", "map height size is too big", game);
}

void	check_width(int width, t_game *game)
{
	if (width < 3)
		error_and_exit("Invalid map",
			"map width size must be 2 or more", game);
	if (width > MAX_WIDTH_IMAGE)
		error_and_exit("Invalid map", "map width size is too big", game);
}

void	check_outer_wall(int x, int y, t_game *game, char map_c)
{
	if (x == 0 || y == 0
		|| x == game->map.width - 1 || y == game->map.height - 1)
	{
		if (map_c != WALL)
			error_and_exit("Invalid map",
				"map must be closed/surrounded by walls.", game);
	}
}

void	check_valid_char(char map_c, t_game *game)
{
	if (map_c != EMPTY && map_c != WALL
		&& map_c != COLLECTIBLE && map_c != EXIT && map_c != PLAYER)
		error_and_exit("Invalid map",
			"map must contain only 0, 1, C, E, and P", game);
}
