#include "so_long.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window.win_ptr);
	exit(0);
}

int	key_check(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window(game);
	if (keycode == UP || keycode == UP_ARROW)
		up_player(game);
	if (keycode == DOWN || keycode == DOWN_ARROW)
		down_player(game);
	if (keycode == LEFT || keycode == LEFT_ARROW)
		left_player(game);
	if (keycode == RIGHT || keycode == RIGHT_ARROW)
		right_player(game);
	return (0);
}

void	game_init(t_game *game)
{
	game->mlx = NULL;
	game->window.win_ptr = NULL;
	game->window.width = 0;
	game->window.height = 0;
	game->map.map_str = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.total_coin = 0;
	game->player.point.x = 0;
	game->player.point.y = 0;
	game->player.move_count = 0;
	game->player.get_coin = 0;
}

bool	diff_extension(char *file_name, char *ext)
{
	int	file_len;
	int	ext_len;

	file_len = ft_strlen(file_name);
	ext_len = ft_strlen(ext);
	if (file_len < ext_len)
		return (false);
	while (ext_len > 0)
	{
		if (file_name[file_len - 1] != ext[ext_len - 1])
			return (false);
		file_len--;
		ext_len--;
	}
	return (true);
}

int	get_fd(char *map_file_path, t_game *game)
{
	int	fd;

	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		error_and_exit("Invalid map file", "failed to open map file", game);
	if (diff_extension(map_file_path, ".ber") == false)
		error_and_exit("Invalid map file", "file extension must be .ber", game);
	return (fd);
}


int	main(int ac, char **av)
{
	t_game	game;
	int		fd;

	game_init(&game);
	if (ac != 2)
		error_and_exit("Invalid arguments", "too few or too many arguments", NULL);
	fd = get_fd(av[1], &game);
	game.map.map_str = get_map(fd, &game);
	check_map(game.map.map_str, &game);
	window_init(&game);
	map_init(&game);

	mlx_hook(game.window.win_ptr, DestroyNotify, StructureNotifyMask, close_window, &game);
	mlx_key_hook(game.window.win_ptr, key_check, &game);
	mlx_loop(game.mlx);
	return (0);
}
