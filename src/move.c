#include "so_long.h"

void	up_player(t_game *game)
{
	int		x;
	int		y;

	x = game->player.point.x;
	y = game->player.point.y;
	if (game->map.map[y - 1][x] == WALL)
	{
		put_message("You can't go up", "That's a wall");
		return ;
	}
	if (game->map.map[y - 1][x] == EXIT)
	{
		if (game->player.get_coin == game->map.total_coin)
		{
			put_message("Congratulations", "CLEAR!");
			close_window(game);
		}
		else
			put_message("You can't leave", "You need to collect all the coin");
		return ;
	}
	if (game->map.map[y - 1][x] == COLLECTIBLE)
		game->player.get_coin += 1;
	put_image(game, EMPTY, x, y);
	game->map.map[y - 1][x] = PLAYER;
	game->map.map[y][x] = EMPTY;
	game->player.point.y -= 1;
	game->player.move_count++;
	ft_printf("Move count: %d\n", game->player.move_count);
	put_image(game, PLAYER, x, y - 1);
}

void	down_player(t_game *game)
{
	int		x;
	int		y;

	x = game->player.point.x;
	y = game->player.point.y;
	if (game->map.map[y + 1][x] == WALL)
	{
		put_message("You can't go down", "That's a wall");
		return ;
	}
	if (game->map.map[y + 1][x] == EXIT)
	{
		if (game->player.get_coin == game->map.total_coin)
		{
			put_message("Congratulations", "CLEAR!");
			close_window(game);
		}
		else
			put_message("You can't leave", "You need to collect all the coin");
		return ;
	}
	if (game->map.map[y + 1][x] == COLLECTIBLE)
		game->player.get_coin += 1;
	put_image(game, EMPTY, x, y);
	game->map.map[y + 1][x] = PLAYER;
	game->map.map[y][x] = EMPTY;
	game->player.point.y += 1;
	game->player.move_count++;
	ft_printf("Move count: %d\n", game->player.move_count);
	put_image(game, PLAYER, x, y + 1);
}

void	left_player(t_game *game)
{
	int		x;
	int		y;

	x = game->player.point.x;
	y = game->player.point.y;
	if (game->map.map[y][x - 1] == WALL)
	{
		put_message("You can't go left", "That's a wall");
		return ;
	}
	if (game->map.map[y][x - 1] == EXIT)
	{
		if (game->player.get_coin == game->map.total_coin)
		{
			put_message("Congratulations", "CLEAR!");
			close_window(game);
		}
		else
			put_message("You can't leave", "You need to collect all the coin");
		return ;
	}
	if (game->map.map[y][x - 1] == COLLECTIBLE)
		game->player.get_coin += 1;
	put_image(game, EMPTY, x, y);
	game->map.map[y][x - 1] = PLAYER;
	game->map.map[y][x] = EMPTY;
	game->player.point.x -= 1;
	game->player.move_count++;
	ft_printf("Move count: %d\n", game->player.move_count);
	put_image(game, PLAYER, x - 1, y);
}

void	right_player(t_game *game)
{
	int		x;
	int		y;

	x = game->player.point.x;
	y = game->player.point.y;
	if (game->map.map[y][x + 1] == WALL)
	{
		put_message("You can't go right", "That's a wall");
		return ;
	}
	if (game->map.map[y][x + 1] == EXIT)
	{
		if (game->player.get_coin == game->map.total_coin)
		{
			put_message("Congratulations", "CLEAR!");
			close_window(game);
		}
		else
			put_message("You can't leave", "You need to collect all the coin");
		return ;
	}
	if (game->map.map[y][x + 1] == COLLECTIBLE)
		game->player.get_coin += 1;
	put_image(game, EMPTY, x, y);
	game->map.map[y][x + 1] = PLAYER;
	game->map.map[y][x] = EMPTY;
	game->player.point.x += 1;
	game->player.move_count++;
	ft_printf("Move count: %d\n", game->player.move_count);
	put_image(game, PLAYER, x + 1, y);
}
