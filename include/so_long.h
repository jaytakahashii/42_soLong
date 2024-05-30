#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# include <stdio.h>
# include "mlx.h"

# include <stdbool.h>
# include <fcntl.h>

typedef struct s_player
{
	size_t	x;
	size_t	y;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	char		**map;
	size_t		window_width;
	size_t		window_height;
	t_player	player;
}				t_game;

typedef struct s_image
{
	void	*path;
	t_game	*game;
	void	*img;
	int		img_height;
	int		img_width;
}				t_image;

void	error_handling(char *message);

void	get_window_size(t_game *game, char *map_file);

void	*put_image(t_image img, size_t x, size_t y);

void	generate_map(char *map_file, t_game *game);

#endif
