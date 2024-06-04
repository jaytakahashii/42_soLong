#include "so_long.h"

void	error_and_exit(char *error_message, char *message, t_game *game)
{
	ft_printf("Error: %s", error_message);
	if (message)
		ft_printf(" (%s)", message);
	if (game->mlx)
		mlx_destroy_window(game->mlx, game->window.win_ptr);
	exit(1);
}

void	put_message(char *error_message, char *message)
{
	ft_printf("%s", error_message);
	if (message)
		ft_printf(": %s", message);
	ft_printf("\n");
}
