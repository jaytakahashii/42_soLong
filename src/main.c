/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:34 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/08 18:16:32 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	key_check(int keycode, t_game *game)
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

static void	game_init(t_game *game)
{
	game->mlx = NULL;
	game->window.win_ptr = NULL;
	game->window.width = 0;
	game->window.height = 0;
	game->map.map_str = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.total_coin = 0;
	game->map.exit_count = 0;
	game->map.player_count = 0;
	game->player.point.x = 0;
	game->player.point.y = 0;
	game->player.move_count = 0;
	game->player.get_coin = 0;
}

void	put_message(char *error_message, char *message)
{
	ft_printf("%s", error_message);
	if (message)
		ft_printf(": %s", message);
	ft_printf("\n");
}

int	main(int ac, char **av)
{
	t_game	game;
	int		fd;

	game_init(&game);
	if (ac != 2)
		error_and_exit("Invalid arguments",
			"Usage: ./so_long [map.ber]", NULL);
	fd = get_fd(av[1]);
	game.map.map_str = get_map(fd);
	check_map(game.map.map_str, &game);
	window_init(&game);
	map_init(&game);
	mlx_hook(game.window.win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK,
		close_window, &game);
	mlx_key_hook(game.window.win_ptr, key_check, &game);
	mlx_loop(game.mlx);
	return (0);
}

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q so_long");
// }
