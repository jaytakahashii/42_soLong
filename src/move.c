#include "so_long.h"

void	update_map(t_game *game, size_t x, size_t y)
{
	t_image	img;

	img.game = game;
	img.path = "textures/empty_42.xpm";
	put_image(img, x * IMAGE_SIZE, y * IMAGE_SIZE);
}

void	up_player(t_game *game)
{
	printf("up\n");
	t_image	img;

	img.game = game;
	if (game->map[game->player.y - 1][game->player.x] == WALL)
		put_message("You can't go up", "That's a wall");
	else if (game->map[game->player.y - 1][game->player.x] == COLLECTIBLE)
	{
		update_map(game, game->player.x, game->player.y);
		img.path = "textures/only_mario_42.xpm";
		game->map[game->player.y - 1][game->player.x] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.y -= 1;
		game->player.collectibles += 1;
		put_image(img, game->player.x * IMAGE_SIZE, game->player.y * IMAGE_SIZE);
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
		update_map(game, game->player.x, game->player.y);
		img.path = "textures/only_mario_42.xpm";
		game->map[game->player.y - 1][game->player.x] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.y -= 1;
		put_image(img, game->player.x * IMAGE_SIZE, game->player.y * IMAGE_SIZE);
	}
}

void	down_player(t_game *game)
{
	printf("down\n");
	t_image	img;

	img.game = game;
	if (game->map[game->player.y + 1][game->player.x] == WALL)
		put_message("You can't go down", "That's a wall");
	else if (game->map[game->player.y + 1][game->player.x] == COLLECTIBLE)
	{
		update_map(game, game->player.x, game->player.y);
		game->map[game->player.y + 1][game->player.x] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.y += 1;
		game->player.collectibles += 1;
		img.path = "textures/only_mario_42.xpm";
		put_image(img, game->player.x * IMAGE_SIZE, game->player.y * IMAGE_SIZE);
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
		update_map(game, game->player.x, game->player.y);
		img.path = "textures/only_mario_42.xpm";
		game->map[game->player.y + 1][game->player.x] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.y += 1;
		put_image(img, game->player.x * IMAGE_SIZE, game->player.y * IMAGE_SIZE);
	}
}

void	left_player(t_game *game)
{
	printf("left\n");
	t_image	img;

	img.game = game;
	if (game->map[game->player.y][game->player.x - 1] == WALL)
		put_message("You can't go left", "That's a wall");
	else if (game->map[game->player.y][game->player.x - 1] == COLLECTIBLE)
	{
		update_map(game, game->player.x, game->player.y);
		game->map[game->player.y][game->player.x - 1] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.x -= 1;
		game->player.collectibles += 1;
		img.path = "textures/only_mario_42.xpm";
		put_image(img, game->player.x * IMAGE_SIZE, game->player.y * IMAGE_SIZE);
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
		update_map(game, game->player.x, game->player.y);
		img.path = "textures/only_mario_42.xpm";
		game->map[game->player.y][game->player.x - 1] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.x -= 1;
		put_image(img, game->player.x * IMAGE_SIZE, game->player.y * IMAGE_SIZE);
	}
}

void	right_player(t_game *game)
{
	printf("right\n");
	t_image	img;

	img.game = game;
	if (game->map[game->player.y][game->player.x + 1] == WALL)
		put_message("You can't go right", "That's a wall");
	else if (game->map[game->player.y][game->player.x + 1] == COLLECTIBLE)
	{
		update_map(game, game->player.x, game->player.y);
		game->map[game->player.y][game->player.x + 1] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.x += 1;
		game->player.collectibles += 1;
		img.path = "textures/only_mario_42.xpm";
		put_image(img, game->player.x * IMAGE_SIZE, game->player.y * IMAGE_SIZE);
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
		update_map(game, game->player.x, game->player.y);
		img.path = "textures/only_mario_42.xpm";
		game->map[game->player.y][game->player.x + 1] = PLAYER;
		game->map[game->player.y][game->player.x] = EMPTY;
		game->player.x += 1;
		put_image(img, game->player.x * IMAGE_SIZE, game->player.y * IMAGE_SIZE);
	}
}
