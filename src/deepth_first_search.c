#include "so_long.h"

static bool	is_valid_point(t_game *game, t_point point, char target)
{
	if (point.x < 1 || point.y < 1 || point.x >= game->map.width - 1 || point.y >= game->map.height - 1)
		return (false);
	if (target == COLLECTIBLE)
	{
		if (game->map.map_str[point.y][point.x] == WALL || game->map.map_str[point.y][point.x] == EXIT)
			return (false);
	}
	else if (target == EXIT)
	{
		if (game->map.map_str[point.y][point.x] == WALL)
			return (false);
	}
	return (true);
}

static void	push(t_stack *stack, t_node *node)
{
	if (stack->top == NULL)
	{
		stack->top = node;
		return ;
	}
	node->next = stack->top;
	stack->top = node;
}

static t_node	*pop(t_stack *stack)
{
	t_node	*node;

	if (stack->top == NULL)
		return (NULL);
	node = stack->top;
	stack->top = stack->top->next;
	return (node);
}

static void	free_stack(t_stack *stack)
{
	t_node	*node;

	while (stack->top != NULL)
	{
		node = pop(stack);
		free(node);
	}
}

t_node	*init_node(t_point point)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->point = point;
	node->next = NULL;
	return (node);
}

bool	is_target(t_game *game, t_point player, char target, int *can_get_coin, t_stack *stack)
{
	if (game->map.map_str[player.y][player.x] == target)
	{
		if (can_get_coin == 0 || target == EXIT)
			free_stack(stack);
			return (true);
		(*can_get_coin)--;
	}
	return (false);
}

int	**basic_vector(int i, int **direction)
{
	if (i == 0)
	{
		direction[i][0] = 1;
		direction[i][1] = 0;
	}
	else if (i == 1)
	{
		direction[i][0] = 0;
		direction[i][1] = 1;
	}
	else if (i == 2)
	{
		direction[i][0] = -1;
		direction[i][1] = 0;
	}
	else if (i == 3)
	{
		direction[i][0] = 0;
		direction[i][1] = -1;
	}
	return (direction);
}

int	**init_direction(void)
{
	int	**direction;
	int	i;

	direction = (int **)malloc(sizeof(int *) * 4);
	if (direction == NULL)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		direction[i] = (int *)malloc(sizeof(int) * 2);
		if (direction[i] == NULL)
			return (NULL);
		direction = basic_vector(i, direction);
		i++;
	}
	return (direction);
}

void	register_next(t_game *game, t_stack *stack, int **visited, t_point next)
{
	t_node	*node;
	t_point	tmp;

	tmp = next;
	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		error_and_exit("Memory allocation error", "failed to allocate memory", game);
	node->point = tmp;
	node->next = NULL;
	push(stack, node);
	visited[next.y][next.x] = 1;
}

int	register_direction(t_game *game, t_stack *stack, int **visited, t_point current, char target)
{
	t_point	next;
	int		**direction;
	int		i;

	i = 0;
	direction = init_direction();
	while (i < 4)
	{
		next = (t_point){current.x + direction[i][0], current.y + direction[i][1]};
		if (is_valid_point(game, next, target) && !visited[next.y][next.x])
		{
			register_next(game, stack, visited, next);
			break ;
		}
		i++;
	}
	free(direction);
	return (i);
}

int	**init_visited(t_game *game)
{
	int	**visited;
	int	i;
	int	j;

	visited = (int **)malloc(sizeof(int *) * game->map.height);
	if (visited == NULL)
		error_and_exit("Memory allocation error", "failed to allocate memory", game);
	i = 0;
	while (i < game->map.height)
	{
		visited[i] = (int *)malloc(sizeof(int) * game->map.width);
		if (visited[i] == NULL)
			error_and_exit("Memory allocation error", "failed to allocate memory", game);
		j = 0;
		while (j < game->map.width)
		{
			visited[i][j] = 0;
			j++;
		}
		i++;
	}
	return (visited);
}

bool	dfs(t_game *game, t_point player, char target, int can_get_coin)
{
	t_stack	stack;
	t_node	*node;
	t_point current;
	int	**visited;
	int		i;

	visited = init_visited(game);
	stack.top = NULL;
	node = init_node(player);
	push(&stack, node);
	visited[player.y][player.x] = 1;
	while (stack.top != NULL)
	{
		current = stack.top->point;
		if (is_target(game, current, target, &can_get_coin, &stack))
			return (true);
		i = register_direction(game, &stack, visited, current, target);
		if (i == 4)
		{
			node = pop(&stack);
			free(node);
		}
	}
	free_stack(&stack);
	return (false);
}
