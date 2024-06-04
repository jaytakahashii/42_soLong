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
	{
		error_and_exit("Invalid map", "map height size is too big", game);
	}
}

static void check_width(int width, t_game *game)
{
	if (width < 3)
		error_and_exit("Invalid map", "map width size must be 2 or more", game);
	if (width > MAX_WIDTH_IMAGE)
	{
		error_and_exit("Invalid map", "map width size is too big", game);
	}
}

static int	strlen_double_ptr(char **str)
{
	int len;

	len = 0;
	while (str[len])
		len++;
	return len;
}

bool	is_outer_wall(int x, int y, t_game *game)
{
	if (x == 0 || y == 0 || x == game->map.width - 1 || y == game->map.height - 1)
		return true;
	return false;
}

bool	is_valid_char(char c)
{
	if (c == EMPTY || c == WALL || c == COLLECTIBLE || c == EXIT || c == PLAYER)
		return true;
	return false;
}

void	basic_map_check(char **map, t_game *game)
{
	int		height;
	int		width;
	char	map_c;
	int		exit_count;
	int		player_count;

	game->map.height = strlen_double_ptr(map);
	game->map.width = (int)ft_strlen(map[0]);
	check_width(game->map.width, game);
	height = -1;
	exit_count = 0;
	player_count = 0;
	while (map[++height])
	{
		width = -1;
		while (map[height][++width])
		{
			map_c = map[height][width];
			if (is_outer_wall(width, height, game) && map_c != WALL)
				error_and_exit("Invalid map", "map must be closed/surrounded by walls.", game);
			if (!is_valid_char(map_c))
				error_and_exit("Invalid map", "map must contain only 0, 1, C, E, and P", game);
			if (map_c == PLAYER)
			{
				player_count++;
				game->player.point.x = width;
				game->player.point.y = height;
				if (player_count > 1)
					error_and_exit("Invalid map", "map must contain only one player", game);
			}
			if (map_c == COLLECTIBLE)
				game->map.total_coin++;
			if (map_c == EXIT)
				exit_count++;
		}
		check_rectangular(game->map.width, width, game);
	}
	if (exit_count == 0 || game->map.total_coin == 0)
		error_and_exit("Invalid map", "map must contain at least one exit and one collectible", game);
	check_height(height, game);
	game->window.width = width * IMAGE_SIZE;
	game->window.height = height * IMAGE_SIZE;
}

void	check_map(char **map, t_game *game)
{
	basic_map_check(map, game);
	clear_check(game);
}
