#include "so_long.h"

void	clear_check(t_game *game)
{
	int		can_get_coin;

	can_get_coin = 0;
	while (can_get_coin < game->map.total_coin)
	{
		if (dfs(game, game->player.point, COLLECTIBLE, can_get_coin) == false)
			error_and_exit("Invalid map", "collectible is not reachable", game);
		can_get_coin++;
	}
	if (dfs(game, game->player.point, EXIT, can_get_coin) == false)
		error_and_exit("Invalid map", "exit is not reachable", game);
}

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
	ssize_t read_bytes;

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
