#include "so_long.h"

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window);
	// mlx_destroy_display(game->mlx);
	// free(game->mlx);
	exit(0);
	// return (0);
}

int	key_check(int keycode, t_game *game)
{
	printf("keycode: %d\n", keycode);
	if (keycode == ESC)
		close_window(game);
	if (keycode == UP)
		up_player(game);
	if (keycode == DOWN)
		down_player(game);
	if (keycode == LEFT)
		left_player(game);
	if (keycode == RIGHT)
		right_player(game);
	return (0);
}

void	game_init(t_game *game)
{
	game->mlx = NULL;
	game->window = NULL;
	game->map = NULL;
	game->window_width = 0;
	game->window_height = 0;
	game->total_collectibles = 0;
	game->player.x = 0;
	game->player.y = 0;
	game->player.collectibles = 0;
}

int	main(int ac, char **av)
{
	t_game	game;

	game_init(&game);
	if (ac != 2)
		error_and_exit("Invalid arguments", "too few or too many arguments", NULL);
	window_init(&game, av[1]);
	map_init(av[1], &game);

	mlx_hook(game.window, DestroyNotify, StructureNotifyMask, close_window, &game);
	mlx_key_hook(game.window, key_check, &game);
	mlx_loop(game.mlx);
	// move player (right: D, left: A, up: W, down: S)
	// mlx_key_hook(game.window, key_hook, &game);
	return (0);
}
