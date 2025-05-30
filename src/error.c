/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:26 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/08 16:28:38 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_and_exit(char *error_message, char *message, t_game *game)
{
	ft_printf(RED"Error: %s"ENDC, error_message);
	if (message)
		ft_printf("  (%s)", message);
	ft_printf("\n");
	if (game && game->mlx && game->window.win_ptr)
		close_window(game);
	if (game && game->map.map_str)
		free_map(game->map.map_str);
	exit(0);
}
