/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:47 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/09 12:58:19 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	repleace_map(t_game *game, t_point point, int up_down, int left_right)
{
	int	x;
	int	y;

	x = point.x;
	y = point.y;
	if (game->map.map_str[y - up_down][x - left_right] == CAN_GET_COIN)
		game->player.get_coin += 1;
	put_image(game, EMPTY, x, y);
	game->map.map_str[y - up_down][x - left_right] = PLAYER;
	game->map.map_str[y][x] = EMPTY;
	game->player.point.x = x - left_right;
	game->player.point.y = y - up_down;
	game->player.move_count++;
	ft_printf("Move count: %d\n", game->player.move_count);
	put_image(game, PLAYER, x - left_right, y - up_down);
}

void	up_player(t_game *game)
{
	int		x;
	int		y;

	x = game->player.point.x;
	y = game->player.point.y;
	if (game->map.map_str[y - 1][x] == WALL)
	{
		put_message(RED"You can't go up"ENDC, "That's a wall");
		return ;
	}
	if (game->map.map_str[y - 1][x] == EXIT)
	{
		if (game->player.get_coin == game->map.total_coin)
		{
			ft_printf("Move count: %d\n", ++(game->player.move_count));
			put_message(GREEN"Congratulations"ENDC, "CLEAR!");
			close_window(game);
		}
		else
			put_message(RED"You can't leave"ENDC,
				"You need to collect all the coin");
		return ;
	}
	repleace_map(game, (t_point){x, y}, 1, 0);
}

void	down_player(t_game *game)
{
	int		x;
	int		y;

	x = game->player.point.x;
	y = game->player.point.y;
	if (game->map.map_str[y + 1][x] == WALL)
	{
		put_message(RED"You can't go down"ENDC, "That's a wall");
		return ;
	}
	if (game->map.map_str[y + 1][x] == EXIT)
	{
		if (game->player.get_coin == game->map.total_coin)
		{
			ft_printf("Move count: %d\n", ++(game->player.move_count));
			put_message(GREEN"Congratulations"ENDC, "CLEAR!");
			close_window(game);
		}
		else
			put_message(RED"You can't leave"ENDC,
				"You need to collect all the coin");
		return ;
	}
	repleace_map(game, (t_point){x, y}, -1, 0);
}

void	left_player(t_game *game)
{
	int		x;
	int		y;

	x = game->player.point.x;
	y = game->player.point.y;
	if (game->map.map_str[y][x - 1] == WALL)
	{
		put_message(RED"You can't go left"ENDC, "That's a wall");
		return ;
	}
	if (game->map.map_str[y][x - 1] == EXIT)
	{
		if (game->player.get_coin == game->map.total_coin)
		{
			ft_printf("Move count: %d\n", ++(game->player.move_count));
			put_message(GREEN"Congratulations"ENDC, "CLEAR!");
			close_window(game);
		}
		else
			put_message(RED"You can't leave"ENDC,
				"You need to collect all the coin");
		return ;
	}
	repleace_map(game, (t_point){x, y}, 0, 1);
}

void	right_player(t_game *game)
{
	int		x;
	int		y;

	x = game->player.point.x;
	y = game->player.point.y;
	if (game->map.map_str[y][x + 1] == WALL)
	{
		put_message(RED"You can't go right"ENDC, "That's a wall");
		return ;
	}
	if (game->map.map_str[y][x + 1] == EXIT)
	{
		if (game->player.get_coin == game->map.total_coin)
		{
			ft_printf("Move count: %d\n", ++(game->player.move_count));
			put_message(GREEN"Congratulations"ENDC, "CLEAR!");
			close_window(game);
		}
		else
			put_message(RED"You can't leave"ENDC,
				"You need to collect all the coin");
		return ;
	}
	repleace_map(game, (t_point){x, y}, 0, -1);
}
