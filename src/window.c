#include "so_long.h"

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

void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->window.win_ptr = mlx_new_window(game->mlx, game->window.width, game->window.height, "so_long");
}
