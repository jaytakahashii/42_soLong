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

#  define UP_ARROW 126
#  define DOWN_ARROW 125
#  define LEFT_ARROW 123
#  define RIGHT_ARROW 124

#  define MAX_WIDTH 2560
#  define MAX_HEIGHT 1400

#  define MAX_WIDTH_IMAGE 60
#  define MAX_HEIGHT_IMAGE 33
#  define MAX_IMAGE 1980
#  define MAX_READ_SIZE 2970

#  define READ_SIZE 3000

#  define DestroyNotify 17
#  define StructureNotifyMask 131072
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

#  define MAX_WIDTH 1920
#  define MAX_HEIGHT 1080

#  define MAX_WIDTH_IMAGE 45
#  define MAX_HEIGHT_IMAGE 25
#  define MAX_IMAGE 1125
#  define MAX_READ_SIZE 1688

#  define READ_SIZE 2000

# endif

# define IMAGE_SIZE 42

# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

# define EMPTY_PATH "textures/empty_42.xpm"
# define WALL_PATH "textures/only_wall_42.xpm"
# define COLLECTIBLE_PATH "textures/only_coin_42.xpm"
# define EXIT_PATH "textures/only_piich_42.xpm"
# define PLAYER_PATH "textures/only_mario_42.xpm"

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_stack
{
	t_point *point;
	struct s_stack *next;
}				t_stack;

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
	int		map_width;
	int		map_height;
	int		window_width;
	int		window_height;
	int		total_collectibles;
	t_player	player;
}				t_game;

// typedef struct s_image
// {
// 	void	*path;
// 	t_game	*game;
// 	void	*img;
// }				t_image;

void	error_and_exit(char *error_message, char *message, t_game *game);

void	put_message(char *error_message, char *message);

void	window_init(t_game *game, char *map_file);

void 	put_image(t_game *game, char map_c, int x, int y);

void	map_init(t_game *game);

char	*get_next_str(int fd);

void	up_player(t_game *game);
void 	down_player(t_game *game);
void 	left_player(t_game *game);
void 	right_player(t_game *game);


int		close_window(t_game *game);

bool	dfs(t_game *game, t_point player, char target);

#endif
