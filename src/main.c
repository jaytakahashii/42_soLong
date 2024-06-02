#include "so_long.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window.window);
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
	game->window.window = NULL;
	game->window.width = 0;
	game->window.height = 0;
	game->map.map = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.total_coin = 0;
	game->player.point.x = 0;
	game->player.point.y = 0;
	game->player.move_count = 0;
	game->player.get_coin = 0;
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		error_and_exit("Invalid arguments", "too few or too many arguments", NULL);
	game_init(&game);
	window_init(&game, av[1]);
	map_init(&game);

	mlx_hook(game.window.window, DestroyNotify, StructureNotifyMask, close_window, &game);
	mlx_key_hook(game.window.window, key_check, &game);
	mlx_loop(game.mlx);
	return (0);
}
