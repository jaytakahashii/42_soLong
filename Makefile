MAKEFILE = Makefile

NAME = so_long

SRC_DIR = src/
OBJ_DIR = .obj/

NAME_LINUX = so_long_linux

LIBFT_NAME = libft.a
LIBFT_DIR = libft/

INCLUDE_DIR = include/
INCLUDE = -I $(INCLUDE_DIR)
LIBFT_INCLUDE = -I $(LIBFT_DIR)$(INCLUDE_DIR)

CC = cc
CFLAGS = -Wall -Wextra -Werror
PEDANTIC = --pedantic
SANITIZE = -fsanitize=address

#macOS
MLX_MAC_FLAGS = -l -framework OpenGL -framework AppKit
#Linux
MLX_LINUX_FLAGS = -lmlx_Linux -lXext -lX11

RM = rm -rf
NORM = norminette

SRC_FILES = main.c\
			error.c\
			window.c\
			file.c\
			map.c\
			utils.c\
			map_utils.c\
			image.c\
			move.c\
			dfs.c\
			dfs_utils.c\
			stack_utils.c\
			get_map.c

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
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT_NAME) $(MLX_MAC_FLAGS) -o $(NAME)
	@echo $(G) "!! $(NAME) created !!" $(X)

$(NAME_LINUX): $(OBJ_DIR) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT_NAME) $(MLX_LINUX_FLAGS) -o $(NAME_LINUX)
	@echo $(G) "!! $(NAME_LINUX) created !!" $(X)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBFT_INCLUDE) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJ_DIR)
	@echo $(R) "$(OBJ_DIR) has been removed.\n" $(X)

fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(OBJ_DIR)
	$(RM) $(NAME) $(NAME_LINUX)
	@echo $(R) "$(NAME) and $(NAME_LINUX) have been removed.\n" $(X)

re: fclean all

relinux: fclean linux

pedantic: CFLAGS += $(PEDANTIC)
pedantic: re
	@echo $(G) "pedantic mode activated.\n" $(X)

leaks: CFLAGS += $(SANITIZE)
leaks: re
	@echo $(G) "leaks mode activated.\n" $(X)

norm:
	@echo $(R) "<<< $(NAME) error count >>>" $(X)
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error | wc -l
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error || true
	@echo "\n"
	@$(MAKE) -C $(LIBFT_DIR) norm

.PHONY: all clean fclean re norm
