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
	printf("Key code: %d\n", keycode);
	if (keycode == ESC)
		close_window(game);
	if (keycode == UP)
		printf("UP\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		error_handling("Invalid arguments", "too few or too many arguments", NULL);
	get_window_size(&game, av[1]);
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, game.window_width, game.window_height, "so_long");

	// generate map
	generate_map(av[1], &game);

	mlx_hook(game.window, DestroyNotify, StructureNotifyMask, close_window, &game);
	mlx_key_hook(game.window, key_check, &game);
	mlx_loop(game.mlx);
	// move player (right: D, left: A, up: W, down: S)
	// mlx_key_hook(game.window, key_hook, &game);
	return (0);
}
