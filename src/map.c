#include "so_long.h"

static void	check_rectangular(int first_line_len, int line_len, t_game *game)
{
	if (first_line_len != line_len)
		error_and_exit("Invalid map", "map width size is not rectangular", game);
}

static void	check_height(int height, t_game *game)
{
	if (height < 3)
		error_and_exit("Invalid map", "map height size must be 2 or more", game);
	if (height > MAX_HEIGHT_IMAGE)
		error_and_exit("Invalid map", "map height size is too big", game);
}

static void check_width(int width, t_game *game)
{
	if (width < 3)
		error_and_exit("Invalid map", "map width size must be 2 or more", game);
	if (width > MAX_WIDTH_IMAGE)
		error_and_exit("Invalid map", "map width size is too big", game);
}

static void	check_map(char **map, t_game *game)
{
	int		height;
	int		width;
	char	map_c;

	check_width((int)ft_strlen(map[0]), game);
	height = 0;
	while (map[height])
	{
		width = 0;
		while (map[height][width])
		{
			map_c = map[height][width];
			if (map_c != EMPTY && map_c != WALL && map_c != COLLECTIBLE && map_c != EXIT && map_c != PLAYER)
				error_and_exit("Invalid map", "map must contain only 0, 1, C, E, and P", game);
			width++;
		}
		check_rectangular((int)ft_strlen(map[0]), width, game);
		height++;
	}
	check_height(height, game);
	game->window_width = width * IMAGE_SIZE;
	game->window_height = height * IMAGE_SIZE;
	game->map_width = width;
	game->map_height = height;
}

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
	if (read_bytes >= MAX_READ_SIZE)
		error_and_exit("Error: Map is too big", NULL, game);
	map_str[read_bytes] = '\0';
	game->map = ft_split(map_str, '\n');
	if (!game->map)
		error_and_exit("Error: Split error", NULL, game);
	free(map_str);
}

bool	is_invalid(int x, int y, t_game *game)
{
	// check if out of map
	if (x > 0 && y > 0 && x < game->map_width && y < game->map_height)
	{
		if (game->map[y][x] != WALL)
			return (true);
	}
	return (false);
}

bool	bfs(t_player player, char target, t_game *game)
{
	int	visited[game->map_height][game->map_width];
	int width;
	int height;
	int *queue;

	// initialize visited
	height = 0;
	while (visited[height])
	{
		width = 0;
		while (visited[height][width])
		{
			visited[height][width] = 0;
			width++;
		}
		height++;
	}
	// initialize queue
	queue = malloc(sizeof(int) * game->map_width * game->map_height);
	if (!queue)
		error_and_exit("Error: Malloc error", NULL, game);

	// bfs
	visited[player.y][player.x] = 1;
	queue[0] = player.y;
	queue[1] = player.x;
	while (queue[0] != -1)
	{
		height = queue[0];
		width = queue[1];
		if (game->map[height][width] == target)
		{
			free(queue);
			return (true);
		}
		if (is_invalid(width + 1, height, game) && visited[height][width + 1] == 0)
		{
			queue[0] = height;
			queue[1] = width + 1;
			visited[height][width + 1] = 1;
		}
		if (is_invalid(width - 1, height, game) && visited[height][width - 1] == 0)
		{
			queue[0] = height;
			queue[1] = width - 1;
			visited[height][width - 1] = 1;
		}
		if (is_invalid(width, height + 1, game) && visited[height + 1][width] == 0)
		{
			queue[0] = height + 1;
			queue[1] = width;
			visited[height + 1][width] = 1;
		}
		if (is_invalid(width, height - 1, game) && visited[height - 1][width] == 0)
		{
			queue[0] = height - 1;
			queue[1] = width;
			visited[height - 1][width] = 1;
		}
	}
	free(queue);
	return (false);
}

// check if can clear map bfs
void	clear_check_map(char **map, t_game *game)
{
	int	height;
	int	width;

	height = 0;
	while (map[height])
	{
		width = 0;
		while (map[height][width])
		{
			if (map[height][width] == COLLECTIBLE)
			{
				if (bfs(game->player, COLLECTIBLE, game) == false)
					error_and_exit("Invalid map", "collectible is not reachable", game);
			}
			if (map[height][width] == EXIT)
			{
				if (bfs(game->player, EXIT, game) == false)
					error_and_exit("Invalid map", "exit is not reachable", game);
			}
			width++;
		}
		height++;
	}
}

void	window_init(t_game *game, char *map_file_path)
{
	int	fd;

	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		error_and_exit("Invalid map file", "failed to open map file", game);
	if (ft_strnstr(map_file_path, ".ber", ft_strlen(map_file_path)) == NULL)
		error_and_exit("Invalid map file", "file extension must be .ber", game);
	get_map(fd, game);
	close(fd);
	check_map(game->map, game);
	// clear_check_map(game->map, game);
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, game->window_width, game->window_height, "so_long");
}

void	map_init(t_game *game)
{
	int		width;
	int		height;

	height = 0;
	while (height < game->map_height)
	{
		width = 0;
		while (width < game->map_width)
		{
			if (game->map[height][width] == PLAYER)
			{
				game->player.x = width;
				game->player.y = height;
			}
			if (game->map[height][width] == COLLECTIBLE)
				game->total_collectibles++;
			put_image(game, game->map[height][width], width, height);
			width++;
		}
		height++;
	}
}
