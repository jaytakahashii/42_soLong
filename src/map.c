/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:44 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/05 02:37:09 by jay              ###   ########.fr       */
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

char	**get_map(int fd, t_game *game)
{
	char	*map_str;
	char	**map;
	ssize_t	read_bytes;

	map_str = malloc(sizeof(char) * READ_SIZE);
	if (!map_str)
		error_and_exit("Error: Malloc error", NULL, game);
	read_bytes = read(fd, map_str, READ_SIZE);
	if (read_bytes < 0)
		error_and_exit("Error: Read error", NULL, game);
	if (read_bytes > MAX_READ_SIZE)
		error_and_exit("Error: Map is too big", NULL, game);
	map_str[read_bytes] = '\0';
	map = ft_split(map_str, '\n');
	if (!map)
		error_and_exit("Error: Split error", NULL, game);
	free(map_str);
	close(fd);
	return (map);
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
			error_and_exit("Invalid map", "collectible is not reachable", game);
		can_get_coin++;
	}
	if (dfs(game, game->player.point, EXIT) == false)
		error_and_exit("Invalid map", "exit is not reachable", game);
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
		error_and_exit("Invalid map", "map must contain only one exit", game);
	if (game->map.total_coin == 0)
		error_and_exit("Invalid map",
			"map must contain at least one collectible", game);
	if (game->map.player_count != 1)
		error_and_exit("Invalid map", "map must contain only one player", game);
	clear_check(game);
}
