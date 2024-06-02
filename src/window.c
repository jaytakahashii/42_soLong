#include "so_long.h"

static void	get_map(int fd, t_game *game)
{
	char	*map_str;
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
	game->map.map = ft_split(map_str, '\n');
	if (!game->map.map)
		error_and_exit("Error: Split error", NULL, game);
	free(map_str);
}

void	window_init(t_game *game, int fd)
{
	get_map(fd, game);
	close(fd);
	check_map_char(game->map.map, game);
	clear_check_map(game);
	game->mlx = mlx_init();
	game->window.window = mlx_new_window(game->mlx, game->window.width, game->window.height, "so_long");
}
