/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:11:07 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/09 12:28:55 by jay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"

# include "mlx.h"

# include <stdbool.h>
# include <fcntl.h>

# ifdef __APPLE__
// key code for mac
#  define ESC 53
#  define UP 13
#  define DOWN 1
#  define LEFT 0
#  define RIGHT 2
#  define UP_ARROW 126
#  define DOWN_ARROW 125
#  define LEFT_ARROW 123
#  define RIGHT_ARROW 124
// max size for mac window
#  define MAX_WIDTH 2560
#  define MAX_HEIGHT 1400
// max size for mac image (42x42) : 2560 / 42 = 60, 1400 / 42 = 33
#  define MAX_WIDTH_IMAGE 60
#  define MAX_HEIGHT_IMAGE 33
// max size for mac image (42x42) : 60 * 33 = 1980
#  define MAX_IMAGE 1980
// max size for mac read :
	//(MAX_WIDTH_IMAGE + 1) * MAX_HEIGHT_IMAGE = 61 * 33 = 2013
#  define MAX_READ_SIZE 2013
#  define READ_SIZE 2500
#  define DESTROYNOTIFY 17
// 1L << 17
#  define STRUCTURENOTIFYMASK 131072
# endif

# ifdef __linux__
// include for linux miniLibX
#  include <X11/X.h>
#  include <X11/keysym.h>
// key code for linux
#  define ESC 65307
#  define UP 119
#  define DOWN 115
#  define LEFT 97
#  define RIGHT 100
#  define UP_ARROW 65362
#  define DOWN_ARROW 65364
#  define LEFT_ARROW 65361
#  define RIGHT_ARROW 65363
// max size for linux window
#  define MAX_WIDTH 1920
#  define MAX_HEIGHT 1080
// max size for linux image (42x42) : 1920 / 42 = 45, 1080 / 42 = 25
#  define MAX_WIDTH_IMAGE 45
#  define MAX_HEIGHT_IMAGE 25
// max size for linux image (42x42) : 45 * 25 = 1125
#  define MAX_IMAGE 1125
// max size for linux read :
	// (MAX_WIDTH_IMAGE + 1) * MAX_HEIGHT_IMAGE = 46 * 25 = 1150
#  define MAX_READ_SIZE 1150
#  define READ_SIZE 1500
#  define DESTROYNOTIFY DestroyNotify
#  define STRUCTURENOTIFYMASK StructureNotifyMask
# endif

# define RED	"\033[1m\033[31m"
# define GREEN	"\033[1m\033[32m"
# define ENDC	"\033[0m"

# define IMAGE_SIZE 42
# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define CAN_GET_COIN 'G'
# define EMPTY_PATH "textures/empty_42.xpm"
# define WALL_PATH "textures/only_wall_42.xpm"
# define COLLECTIBLE_PATH "textures/only_coin_42.xpm"
# define EXIT_PATH "textures/only_piich_42.xpm"
# define PLAYER_PATH "textures/only_mario_42.xpm"

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_node
{
	t_point			point;
	struct s_node	*next;
}				t_node;

typedef struct s_stack
{
	t_node	*top;
}				t_stack;

typedef struct s_player
{
	t_point	point;
	int		move_count;
	int		get_coin;
}				t_player;

typedef struct s_window
{
	void	*win_ptr;
	int		width;
	int		height;
}				t_window;

typedef struct s_map
{
	char	**map_str;
	int		width;
	int		height;
	int		total_coin;
	int		player_count;
	int		exit_count;
}				t_map;

typedef struct s_dfs
{
	t_stack	stack;
	t_point	current;
	int		**visited;
	int		**direction;
}				t_dfs;

typedef struct s_game
{
	void		*mlx;
	t_window	window;
	t_map		map;
	t_player	player;
}				t_game;

// error.c
void	error_and_exit(char *error_message, char *message, t_game *game);

// main.c
void	put_message(char *error_message, char *message);

// file.c
int		get_fd(char *file_name);

// get_map.c
char	**get_map(int fd);

// map.c
void	check_map(char **map, t_game *game);
void	basic_map_check(char **map, t_game *game);
void	clear_check(t_game *game);
void	map_init(t_game *game);

// map_utils.c
void	check_width(int width, t_game *game);
void	check_outer_wall(int x, int y, t_game *game, char map_c);
void	check_valid_char(char map_c, t_game *game);
void	check_rectangular(int first_line_len, int line_len, t_game *game);
void	check_height(int height, t_game *game);

// utils.c
int		strlen_double_ptr(char **str);
void	add_player(t_game *game, int x, int y, char map_c);
void	free_map(char **map);
void	dfs_init(t_dfs *dfs);

// dfs.c
bool	dfs(t_game *game, t_point player, char target);

// window.c
void	window_init(t_game *game);
int		close_window(t_game *game);

// image.c
void	put_image(t_game *game, char map_c, int x, int y);

// move.c
void	up_player(t_game *game);
void	down_player(t_game *game);
void	left_player(t_game *game);
void	right_player(t_game *game);

// stack_utils.c
bool	push(t_stack *stack, t_point point);
t_node	*pop(t_stack *stack);
t_node	*init_node(t_point point);
void	free_stack(t_stack *stack);

// dfs_utils.c
bool	is_valid_point(t_game *game, t_point point, char target);
bool	is_target(t_game *game, char target, t_dfs *dfs);
int		**basic_vector(int i, int **direction);
void	free_dfs(t_dfs *dfs, t_game *game);
void	free_int_matrix(int **matrix, int height);

#endif
