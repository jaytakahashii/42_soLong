#include "so_long.h"

void	up_player(t_game *game)
{
	printf("up\n");
	if (game->map[game->player.y - 1][game->player.x] == WALL)
		put_message("You can't go up", "That's a wall");
	else if (game->map[game->player.y - 1][game->player.x] == COLLECTIBLE)
	{
		put_image(game, COLLECTIBLE, game->player.x, game->player.y);
		game->map[game->player.y - 1][game->player.x] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.y -= 1;
		game->player.collectibles += 1;
		put_image(game, PLAYER, game->player.x, game->player.y);
	}
	else if (game->map[game->player.y - 1][game->player.x] == EXIT)
	{
		if (game->player.collectibles == game->total_collectibles)
		{
			put_message("Congratulations", "CLEAR!");
			close_window(game);
		}
		else
			put_message("You can't leave", "You need to collect all the coin");
	}
	else
	{
		put_image(game, EMPTY, game->player.x, game->player.y);
		game->map[game->player.y - 1][game->player.x] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.y -= 1;
		put_image(game, PLAYER, game->player.x, game->player.y);
	}
}

void	down_player(t_game *game)
{
	printf("down\n");
	if (game->map[game->player.y + 1][game->player.x] == WALL)
		put_message("You can't go down", "That's a wall");
	else if (game->map[game->player.y + 1][game->player.x] == COLLECTIBLE)
	{
		put_image(game, COLLECTIBLE, game->player.x, game->player.y);
		game->map[game->player.y + 1][game->player.x] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.y += 1;
		game->player.collectibles += 1;
		put_image(game, PLAYER, game->player.x, game->player.y);
	}
	else if (game->map[game->player.y + 1][game->player.x] == EXIT)
	{
		if (game->player.collectibles == game->total_collectibles)
		{
			put_message("Congratulations", "CLEAR!");
			close_window(game);
		}
		else
			put_message("You can't leave", "You need to collect all the coin");
	}
	else
	{
		put_image(game, EMPTY, game->player.x, game->player.y);
		game->map[game->player.y + 1][game->player.x] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.y += 1;
		put_image(game, PLAYER, game->player.x, game->player.y);
	}
}

void	left_player(t_game *game)
{
	printf("left\n");
	if (game->map[game->player.y][game->player.x - 1] == WALL)
		put_message("You can't go left", "That's a wall");
	else if (game->map[game->player.y][game->player.x - 1] == COLLECTIBLE)
	{
		put_image(game, COLLECTIBLE, game->player.x, game->player.y);
		game->map[game->player.y][game->player.x - 1] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.x -= 1;
		game->player.collectibles += 1;
		put_image(game, PLAYER, game->player.x, game->player.y);
	}
	else if (game->map[game->player.y][game->player.x - 1] == EXIT)
	{
		if (game->player.collectibles == game->total_collectibles)
		{
			put_message("Congratulations", "CLEAR!");
			close_window(game);
		}
		else
			put_message("You can't leave", "You need to collect all the coin");
	}
	else
	{
		put_image(game, EMPTY, game->player.x, game->player.y);
		game->map[game->player.y][game->player.x - 1] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.x -= 1;
		put_image(game, PLAYER, game->player.x, game->player.y);
	}
}

void	right_player(t_game *game)
{
	printf("right\n");
	if (game->map[game->player.y][game->player.x + 1] == WALL)
		put_message("You can't go right", "That's a wall");
	else if (game->map[game->player.y][game->player.x + 1] == COLLECTIBLE)
	{
		put_image(game, COLLECTIBLE, game->player.x, game->player.y);
		game->map[game->player.y][game->player.x + 1] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.x += 1;
		game->player.collectibles += 1;
		put_image(game, PLAYER, game->player.x, game->player.y);
	}
	else if (game->map[game->player.y][game->player.x + 1] == EXIT)
	{
		if (game->player.collectibles == game->total_collectibles)
		{
			put_message("Congratulations", "CLEAR!");
			close_window(game);
		}
		else
			put_message("You can't leave", "You need to collect all the coin");
	}
	else
	{
		put_image(game, EMPTY, game->player.x, game->player.y);
		game->map[game->player.y][game->player.x + 1] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.x += 1;
		put_image(game, PLAYER, game->player.x, game->player.y);
	}
}
