#include "so_long.h"

void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->window.win_ptr = mlx_new_window(game->mlx, game->window.width, game->window.height, "so_long");
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->window.win_ptr);
	exit(0);
}
