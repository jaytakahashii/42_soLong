NAME = so_long
NAME_LINUX = so_long_linux
LIBFT_NAME = libft
LIBFT_DIR = libft/
INCLUDE_DIR = include/
INCLUDE = -I $(INCLUDE_DIR)
LIBFT_INCLUDE = -I $(LIBFT_DIR)$(INCLUDE_DIR)
SRC_DIR = src/
OBJ_DIR = .obj/
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_MAC_FLAGS = -L mlx -l mlx -framework OpenGL -framework AppKit
MLX_LINUX_FLAGS = -lmlx_Linux -lXext -lX11

AR = ar
ARFLAGS = rcs
RM = rm -rf
NORM = norminette

SRC_FILES = main.c\
			map.c\
			image.c\
			error.c\
			get_next_str.c\
			move.c\
			deepth_first_search.c

OBJ_FILES = $(SRC_FILES:%.c=%.o)

SRCS += $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS += $(addprefix $(OBJ_DIR), $(OBJ_FILES))

Y 			= "\033[33m"
R 			= "\033[31m"
G 			= "\033[32m"
B 			= "\033[34m"
X 			= "\033[0m"
UP 			= "\033[A"
CUT 		= "\033[K"

all: $(NAME)

linux: $(NAME_LINUX)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "\n"
	@echo $(B) "--> Into $(LIBFT_DIR)" $(X)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo $(B) "*** $(NAME) creating ***" $(X)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT_NAME) $(MLX_MAC_FLAGS) -o $(NAME)
	@echo "\n"
	@echo $(G) "!!!!!!! $(NAME) created success !!!!!!!" $(X)

$(NAME_LINUX): $(OBJ_DIR) $(OBJS)
	@echo "\n"
	@echo $(B) "--> Into $(LIBFT_DIR)" $(X)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo $(B) "*** $(NAME_LINUX) creating ***" $(X)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT_NAME) $(MLX_LINUX_FLAGS) -o $(NAME_LINUX)
	@echo "\n"
	@echo $(G) "!!!!!!! $(NAME_LINUX) created success !!!!!!!" $(X)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo $(B) "Compiling $< into $@" $(X)
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBFT_INCLUDE) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo $(R) "<< $(NAME) cleaning>>" $(X)
	$(RM) $(OBJ_DIR)
	@echo "\n"

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo $(R) "<< $(NAME) fcleaning >>" $(X)
	$(RM) $(OBJ_DIR)
	$(RM) $(NAME) $(NAME_LINUX)
	@echo "\n"

re: fclean all

relinux: fclean linux

norm:
	@echo $(R) "<<< $(NAME) error count >>>" $(X)
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error | wc -l
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error || true
	@echo "\n"
	@$(MAKE) -C $(LIBFT_DIR) norm

.PHONY: all clean fclean re norm
