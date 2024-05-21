NAME = so_long
LIBFT_NAME = libft
LIBFT_DIR = libft/
INCLUDE_DIR = include/
INCLUDE = -I $(INCLUDE_DIR)
LIBFT_INCLUDE = -I $(LIBFT_DIR)$(INCLUDE_DIR)
SRC_DIR = src/
OBJ_DIR = .obj/
CC = cc
CFLAGS = -Wall -Wextra -Werror
MINILIBX = -L mlx -l mlx -framework OpenGL -framework AppKit
AR = ar
ARFLAGS = rcs
RM = rm -rf
NORM = norminette

SRC_FILES = main.c

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

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "\n"
	@echo $(B) "--> Into libft directory" $(X)
	@$(MAKE) -C $(LIBFT_DIR)
	@echo $(B) "*** $(NAME) creating ***" $(X)
	$(CC) $(CFLAGS) $(MINILIBX) $(OBJS) $(LIBFT_DIR)$(LIBFT_NAME) -o $(NAME)
	@echo "\n"
	@echo $(G) "!!!!!!! $(NAME) created success !!!!!!!" $(X)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
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
	$(RM) $(NAME)
	@echo "\n"

re: fclean all

norm:
	@echo $(R) "<<< $(NAME) error count >>>" $(X)
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error | wc -l
	@norminette $(SRC_DIR) $(INCLUDE_DIR) | grep Error || true
	@echo "\n"
	@$(MAKE) -C $(LIBFT_DIR) norm

.PHONY: all clean fclean re norm
