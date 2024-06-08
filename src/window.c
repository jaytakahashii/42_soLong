/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:50:00 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/08 16:37:13 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->window.win_ptr = mlx_new_window(game->mlx,
			game->window.width,
			game->window.height,
			"so_long");
}

int	close_window(t_game *game)
{
	if (game->map.map_str)
	{
		free_map(game->map.map_str);
		printf("Map has been freed\n");
	}
	mlx_destroy_window(game->mlx, game->window.win_ptr);
	exit(0);
}
