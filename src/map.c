#include "so_long.h"

static void	calculate_window_size(int fd, t_game *game)
{
	char	*line;
	size_t	width;
	size_t	height;

	line = get_next_str(fd);
	if (!line)
		error_handling("Error: Invalid map file\n");
	width = ft_strlen(line);
	height = 1;
	while (1)
	{
		line = get_next_str(fd);
		if (!line)
			break ;
		if (ft_strlen(line) != width)
			error_handling("Error: Invalid map file\n");
		height++;
	}
	game->window_width = width * 42;
	game->window_height = height * 42;
	printf("width / 42: %lu\n", width);
	printf("height / 42: %lu\n", height);
}

// get window size
void	get_window_size(t_game *game, char *map_file)
{
	int	fd;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_handling("Error: Invalid map file\n");
	if (ft_strnstr(map_file, ".ber", ft_strlen(map_file)) == NULL)
		error_handling("Error: Invalid map file\n");
	calculate_window_size(fd, game);
	close(fd);
}

#include <string.h>

void	put_floor(t_game *game, size_t height)
{
	size_t	width;
	t_image	img;

	width = 0;
	img.game = game;
	img.img_height = 42;
	img.img_width = 42;
	while (width < game->window_width / 42)
	{
		if (game->map[height][width] == '0')
		{
			img.path = "./textures/empty_42.xpm";
			put_image(img, width * 42, height * 42);
		}
		if (game->map[height][width] == '1')
		{
			img.path = "./textures/only_wall_42.xpm";
			put_image(img, width * 42, height * 42);
		}
		else if (game->map[height][width] == 'C')
		{
			img.path = "./textures/only_raion_42.xpm";
			put_image(img, width * 42, height * 42);
		}
		else if (game->map[height][width] == 'E')
		{
			img.path = "./textures/only_piich_42.xpm";
			put_image(img, width * 42, height * 42);
		}
		else if (game->map[height][width] == 'P')
		{
			img.path = "./textures/only_mario_42.xpm";
			put_image(img, width * 42, height * 42);
		}
		printf("%c", game->map[height][width]);
		// else
		// 	error_handling("Error: Invalid map fileeeeee\n");
		width++;
	}
	printf("\n");
}

void	put_map(t_game *game, char *line, size_t height)
{
	size_t	width = 0;

	// game->map[height] = (char *)malloc(sizeof(char) * ((game->window_width / 42) + 1));
	game->map[height] = (char *)malloc(1000);
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
	game->map[game->window_height / 42] = NULL;
	fd = open(map_file, O_RDONLY);
	height = 0;
	while (height < game->window_height / 42)
	{
		line = get_next_str(fd);
		if (!line)
			error_handling("Error: Invalid map[[[ file\n");
		printf("うごかい？%d\n", (int)height);
		put_map(game, line, height);
		height++;
	}
	(void)line;
}
