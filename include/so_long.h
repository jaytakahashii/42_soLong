#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# include "mlx.h"

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>

# ifdef __APPLE__
#  define ESC 53
#  define UP 13
#  define DOWN 1
#  define LEFT 0
#  define RIGHT 2
# endif

# ifdef __linux__
#  include <stdio.h>
#  include <X11/X.h>
#  include <X11/keysym.h>

#  define ESC 65307

#  define UP 119
#  define DOWN 115
#  define LEFT 97
#  define RIGHT 100

#  define UP_ARROW 65362
#  define DOWN_ARROW 65364
#  define LEFT_ARROW 65361
#  define RIGHT_ARROW 65363

# endif

# define IMAGE_SIZE 42

# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

typedef struct s_player
{
	int	x;
	int	y;
	int		move_count;
	int	collectibles;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	char		**map;
	int		window_width;
	int		window_height;
	int		total_collectibles;
	t_player	player;
}				t_game;

typedef struct s_image
{
	void	*path;
	t_game	*game;
	void	*img;
}				t_image;

void	error_and_exit(char *error_message, char *message, t_game *game);

void	put_message(char *error_message, char *message);

void	window_init(t_game *game, char *map_file);

void	*put_image(t_image img, int x, int y);

void	map_init(char *map_file, t_game *game);

char	*get_next_str(int fd);

void	up_player(t_game *game);
void 	down_player(t_game *game);
void 	left_player(t_game *game);
void 	right_player(t_game *game);


int		close_window(t_game *game);

#endif
