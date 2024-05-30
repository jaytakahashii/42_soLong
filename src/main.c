#include "so_long.h"

int	main(int ac, char **av)
{
	t_game	game;

	// error handling for invalid arguments too many or too few
	if (ac != 2)
		error_handling("Error: Invalid arguments\n");
	get_window_size(&game, av[1]);
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, game.window_width, game.window_height, "so_long");

	// generate map
	generate_map(av[1], &game);

	mlx_loop(game.mlx);
	return (0);
}
