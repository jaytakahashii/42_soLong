#include "so_long.h"

void	error_and_exit(char *error_message, char *message, t_game *game)
{
	ft_printf("Error: %s", error_message);
	if (message)
		ft_printf(" (%s)", message);
	ft_printf("\n");
	if (game)
	{
		mlx_destroy_window(game->mlx, game->window);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(1);
}

void	put_message(char *error_message, char *message)
{
	ft_printf("%s", error_message);
	if (message)
		ft_printf(": %s", message);
	ft_printf("\n");
}
