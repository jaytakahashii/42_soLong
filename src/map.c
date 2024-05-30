#include "so_long.h"

static void	calculate_window_size(int fd, t_game *game)
{
	char	*line;
	size_t	width;
	size_t	height;

	line = get_next_line(fd);
	if (!line)
		error_handling("Error: Invalid map file\n");
	width = ft_strlen(line) - 1;
	height = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) - 1 != width)
			error_handling("Error: Invalid map file\n");
		height++;
	}
	game->window_width = width * 42;
	game->window_height = height * 42;
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

void	put_floor(t_game *game, int i)
{
	int	j;
	t_image	img;

	j = 0;
	img.game = game;
	img.path = "./textures/only_wall_42.xpm";
	img.img_height = 42;
	img.img_width = 42;
	while (game->map[i][j])
	{
		if (game->map[i][j] == '0')
			put_image(img, j * 42, i * 42);
		j++;
	}
}

void	put_map(t_game *game, char *line, int i)
{
	int	j = 0;

	game->map[i] = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[j])
	{
		game->map[i][j] = line[j];
		j++;
	}
	free(line);
	game->map[i][j] = '\0';
	put_floor(game, i);
}

void	generate_map(char *map_file, t_game *game)
{
	int		fd;
	char	*line;
	size_t	i;

	game->map = (char **)malloc(sizeof(char *) * ((game->window_height / 42) + 1));
	fd = open(map_file, O_RDONLY);
	i = 0;
	while (i <= game->window_height / 42)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		put_map(game, line, i);
		i++;
	}
}
