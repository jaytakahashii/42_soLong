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

void	check_outer_wall(int x, int y, t_game *game, char map_c)
{
	if (x == 0 || y == 0 || x == game->map.width - 1 || y == game->map.height - 1)
	{
		if (map_c != WALL)
			error_and_exit("Invalid map", "map must be closed/surrounded by walls.", game);
	}
}

void	check_valid_char(char c, t_game *game)
{
	if (c != EMPTY && c != WALL && c != COLLECTIBLE && c != EXIT && c != PLAYER)
		error_and_exit("Invalid map", "map must contain only 0, 1, C, E, and P", game);
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
		error_and_exit("Invalid map", "map must contain only one player", game);
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
	game->window.width = width * IMAGE_SIZE;
	game->window.height = height * IMAGE_SIZE;
}

void	check_map(char **map, t_game *game)
{
	game->map.height = strlen_double_ptr(map);
	game->map.width = (int)ft_strlen(map[0]);
	check_width(game->map.width, game);
	basic_map_check(map, game);
	if (game->map.exit_count != 1)
		error_and_exit("Invalid map", "map must contain only one exit", game);
	if (game->map.total_coin == 0)
		error_and_exit("Invalid map", "map must contain at least one collectible", game);
	if (game->map.player_count != 1)
		error_and_exit("Invalid map", "map must contain only one player", game);
	clear_check(game);
}
