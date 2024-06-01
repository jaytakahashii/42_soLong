#include "so_long.h"

void	up_player(t_game *game)
{
	if (game->map[game->player.y - 1][game->player.x] == WALL)
	{
		put_message("You can't go up", "That's a wall");
		return ;
	}
	if (game->map[game->player.y - 1][game->player.x] == EXIT)
	{
		if (game->player.collectibles == game->total_collectibles)
		{
			put_message("Congratulations", "CLEAR!");
			close_window(game);
		}
		else
			put_message("You can't leave", "You need to collect all the coin");
		return ;
	}
	if (game->map[game->player.y - 1][game->player.x] == COLLECTIBLE)
		game->player.collectibles += 1;
	put_image(game, EMPTY, game->player.x, game->player.y);
	game->map[game->player.y - 1][game->player.x] = PLAYER;
	game->map[game->player.y][game->player.x] = EMPTY;
	game->player.y -= 1;
	put_image(game, PLAYER, game->player.x, game->player.y);
}

void	down_player(t_game *game)
{
	if (game->map[game->player.y + 1][game->player.x] == WALL)
	{
		put_message("You can't go down", "That's a wall");
		return ;
	}
	if (game->map[game->player.y + 1][game->player.x] == EXIT)
	{
		if (game->player.collectibles == game->total_collectibles)
		{
			put_message("Congratulations", "CLEAR!");
			close_window(game);
		}
		else
			put_message("You can't leave", "You need to collect all the coin");
		return ;
	}
	if (game->map[game->player.y + 1][game->player.x] == COLLECTIBLE)
		game->player.collectibles += 1;
	put_image(game, EMPTY, game->player.x, game->player.y);
	game->map[game->player.y + 1][game->player.x] = PLAYER;
	game->map[game->player.y][game->player.x] = EMPTY;
	game->player.y += 1;
	put_image(game, PLAYER, game->player.x, game->player.y);
}

void	left_player(t_game *game)
{
	if (game->map[game->player.y][game->player.x - 1] == WALL)
	{
		put_message("You can't go left", "That's a wall");
		return ;
	}
	if (game->map[game->player.y][game->player.x - 1] == EXIT)
	{
		if (game->player.collectibles == game->total_collectibles)
		{
			put_message("Congratulations", "CLEAR!");
			close_window(game);
		}
		else
			put_message("You can't leave", "You need to collect all the coin");
		return ;
	}
	if (game->map[game->player.y][game->player.x - 1] == COLLECTIBLE)
		game->player.collectibles += 1;
	put_image(game, EMPTY, game->player.x, game->player.y);
	game->map[game->player.y][game->player.x - 1] = PLAYER;
	game->map[game->player.y][game->player.x] = EMPTY;
	game->player.x -= 1;
	put_image(game, PLAYER, game->player.x, game->player.y);
}

void	right_player(t_game *game)
{
	if (game->map[game->player.y][game->player.x + 1] == WALL)
	{
		put_message("You can't go right", "That's a wall");
		return ;
	}
	if (game->map[game->player.y][game->player.x + 1] == EXIT)
	{
		if (game->player.collectibles == game->total_collectibles)
		{
			put_message("Congratulations", "CLEAR!");
			close_window(game);
		}
		else
			put_message("You can't leave", "You need to collect all the coin");
		return ;
	}
	if (game->map[game->player.y][game->player.x + 1] == COLLECTIBLE)
		game->player.collectibles += 1;
	put_image(game, EMPTY, game->player.x, game->player.y);
	game->map[game->player.y][game->player.x + 1] = PLAYER;
	game->map[game->player.y][game->player.x] = EMPTY;
	game->player.x += 1;
	put_image(game, PLAYER, game->player.x, game->player.y);
}
