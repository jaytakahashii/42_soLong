#include "so_long.h"

void	error_handling(char *error_message, char *message, t_game *game)
{
	ft_printf("Error: %s\n", error_message);
	if (message)
		ft_printf("%s\n", message);
	if (game)
	{
		mlx_destroy_window(game->mlx, game->window);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(1);
}
