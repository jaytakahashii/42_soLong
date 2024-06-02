#include "so_long.h"

static bool	is_valid_point(t_game *game, t_point point)
{
	if (point.x < 1 || point.y < 1 || point.x >= game->map_width - 1 || point.y >= game->map_height - 1)
	{
		return (false);
	}
	if (game->map[point.y][point.x] == WALL)
	{
		return (false);
	}
	return (true);
}

static void	push(t_stack *stack, t_node *node)
{
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

bool	dfs(t_game *game, t_point player, char target)
{
	t_stack	stack;
	t_node	*node;
	t_point	point;
	t_point current;
	t_point	next;
	int		direction[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	int		visited[game->map_height][game->map_width];
	int		i;

	ft_memset(visited, 0, sizeof(visited));
	stack.top = NULL;
	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		error_and_exit("Memory allocation error", "failed to allocate memory", game);
	node->point = player;
	node->next = NULL;
	push(&stack, node);
	visited[player.y][player.x] = 1;
	while (stack.top != NULL)
	{
		current = stack.top->point;
		if (game->map[current.y][current.x] == target)
		{
			free_stack(&stack);
			return (true);
		}
		i = 0;
		while (i < 4)
		{
			next.x = current.x + direction[i][0];
			next.y = current.y + direction[i][1];
			if (is_valid_point(game, next) && !visited[next.y][next.x])
			{
				point = next;
				node = (t_node *)malloc(sizeof(t_node));
				if (node == NULL)
					error_and_exit("Memory allocation error", "failed to allocate memory", game);
				node->point = point;
				node->next = NULL;
				push(&stack, node);
				visited[next.y][next.x] = 1;
				break;
			}
			i++;
		}
		if (i == 4)
		{
			node = pop(&stack);
			free(node);
		}
	}
	free_stack(&stack);
	return (false);
}
