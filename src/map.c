/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:44 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/05 13:49:45 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_init(t_game *game)
{
	int		width;
	int		height;

	height = 0;
	while (height < game->map.height)
	{
		width = 0;
		while (width < game->map.width)
		{
			put_image(game, game->map.map_str[height][width], width, height);
			width++;
		}
		height++;
	}
}

void	basic_map_check(char **map, t_game *game)
{
	int		height;
	int		width;
	char	map_c;

	height = -1;
	while (map[++height])
	{
		width = -1;
		while (map[height][++width])
		{
			map_c = map[height][width];
			check_outer_wall(width, height, game, map_c);
			check_valid_char(map_c, game);
			add_player(game, width, height, map_c);
			if (map_c == COLLECTIBLE)
				game->map.total_coin++;
			if (map_c == EXIT)
				game->map.exit_count++;
		}
		check_rectangular(game->map.width, width, game);
	}
	check_height(height, game);
}

void	clear_check(t_game *game)
{
	int		can_get_coin;

	can_get_coin = 0;
	while (can_get_coin < game->map.total_coin)
	{
		if (dfs(game, game->player.point, COLLECTIBLE) == false)
			error_and_exit("Invalid map", "collectible is not reachable", NULL);
		can_get_coin++;
	}
	if (dfs(game, game->player.point, EXIT) == false)
		error_and_exit("Invalid map", "exit is not reachable", NULL);
}

void	check_map(char **map, t_game *game)
{
	game->map.height = strlen_double_ptr(map);
	game->map.width = (int)ft_strlen(map[0]);
	check_width(game->map.width, game);
	basic_map_check(map, game);
	game->window.width = game->map.width * IMAGE_SIZE;
	game->window.height = game->map.height * IMAGE_SIZE;
	if (game->map.exit_count != 1)
		error_and_exit("Invalid map", "map must contain only one exit", NULL);
	if (game->map.total_coin == 0)
		error_and_exit("Invalid map",
			"map must contain at least one collectible", NULL);
	if (game->map.player_count != 1)
		error_and_exit("Invalid map", "map must contain only one player", NULL);
	clear_check(game);
}
