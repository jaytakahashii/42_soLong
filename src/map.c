#include "so_long.h"

static void	calculate_window_size(int fd, t_game *game)
{
	char	*line;
	size_t	width;
	size_t	height;

	line = get_next_str(fd);
	if (!line)
		error_handling("GNL error", "failed to read map file", game);
	width = ft_strlen(line);
	height = 1;
	while (1)
	{
		line = get_next_str(fd);
		if (!line)
			break ;
		if (ft_strlen(line) != width)
			error_handling("Invalid map", "map must be rectangular", game);
		height++;
	}
	game->window_width = width * 42;
	game->window_height = height * 42;
}

// get window size
void	get_window_size(t_game *game, char *map_file_name)
{
	int	fd;

	fd = open(map_file_name, O_RDONLY);
	if (fd < 0)
		error_handling("Invalid map file", "failed to open map file", game);
	if (ft_strnstr(map_file_name, ".ber", ft_strlen(map_file_name)) == NULL)
		error_handling("Invalid map file", "file extension must be .ber", game);
	calculate_window_size(fd, game);
	close(fd);
}

#include <string.h>

void	put_floor(t_game *game, size_t height)
{
	size_t	width;
	t_image	img;
	char	map_c;

	width = 0;
	img.game = game;
	img.img_height = 42;
	img.img_width = 42;
	while (width < game->window_width / 42)
	{
		map_c = game->map[height][width];
		if (map_c != '0' && map_c != '1' && map_c != 'C' && map_c != 'E' && map_c != 'P')
			error_handling("Invalid map", "map must contain only 0, 1, C, E, and P", game);
		if (map_c == '0')
		{
			img.path = "./textures/empty_42.xpm";
			put_image(img, width * 42, height * 42);
		}
		if (map_c == '1')
		{
			img.path = "./textures/only_wall_42.xpm";
			put_image(img, width * 42, height * 42);
		}
		else if (map_c == 'C')
		{
			img.path = "./textures/only_raion_42.xpm";
			put_image(img, width * 42, height * 42);
		}
		else if (map_c == 'E')
		{
			img.path = "./textures/only_piich_42.xpm";
			put_image(img, width * 42, height * 42);
		}
		else if (map_c == 'P')
		{
			img.path = "./textures/only_mario_42.xpm";
			put_image(img, width * 42, height * 42);
		}
		width++;
	}
}

void	put_map(t_game *game, char *line, size_t height)
{
	size_t	width = 0;

	// game->map[height] = (char *)malloc(sizeof(char) * ((game->window_width / 42) + 1));
	game->map[height] = (char *)malloc(1000);
	if (!game->map[height])
		error_handling("Error: Malloc error", NULL, game);
	while (width < game->window_width)
	{
		game->map[height][width] = line[width];
		width++;
	}
	game->map[height][width] = '\0';
	put_floor(game, height);
}

void	generate_map(char *map_file, t_game *game)
{
	int		fd;
	char	*line;
	size_t	height;

	// game->map = (char **)malloc(sizeof(char *) * ((game->window_height / 42) + 1));
	game->map = (char **)malloc(1000);
	if (!game->map)
		error_handling("Error: Malloc error", NULL, game);
	game->map[game->window_height / 42] = NULL;
	fd = open(map_file, O_RDONLY);
	height = 0;
	while (height < game->window_height / 42)
	{
		line = get_next_str(fd);
		if (!line)
			error_handling("Error: GNL error", NULL, game);
		put_map(game, line, height);
		height++;
	}
}
