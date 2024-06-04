/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:31 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/05 02:35:45 by jay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_game *game, char map_c, int x, int y)
{
	void	*img;
	int		image_size;

	img = NULL;
	image_size = IMAGE_SIZE;
	if (map_c == EMPTY)
		img = mlx_xpm_file_to_image(game->mlx,
				"./textures/empty_42.xpm", &image_size, &image_size);
	else if (map_c == WALL)
		img = mlx_xpm_file_to_image(game->mlx,
				"./textures/only_wall_42.xpm", &image_size, &image_size);
	else if (map_c == CAN_GET_COIN)
		img = mlx_xpm_file_to_image(game->mlx,
				"./textures/only_coin_42.xpm", &image_size, &image_size);
	else if (map_c == EXIT)
		img = mlx_xpm_file_to_image(game->mlx,
				"./textures/only_piich_42.xpm", &image_size, &image_size);
	else if (map_c == PLAYER)
		img = mlx_xpm_file_to_image(game->mlx,
				"./textures/only_mario_42.xpm", &image_size, &image_size);
	mlx_put_image_to_window(game->mlx, game->window.win_ptr,
		img, x * IMAGE_SIZE, y * IMAGE_SIZE);
}
