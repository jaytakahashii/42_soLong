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

void	ft_lstremove_front(t_list **lst)
{
	t_list	*tmp;

	if (!lst || !*lst)
		return ;
	tmp = *lst;
	*lst = tmp->next;
	free(tmp);
}

bool	dfs(t_game *game, t_point player, char target)
{
	int	visited[game->map_height][game->map_width];
	int	directions[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
	t_point	next;
	t_list	*stack;
	int	i;

	i = 0;
	while (i < game->map_height)
	{
		ft_memset(visited[i], 0, game->map_width * sizeof(int));
		i++;
	}
	stack = ft_lstnew(&player);
	visited[player.y][player.x] = 1;

	while (stack)
	{
		player = *(t_point *)stack->content;
		if (game->map[player.y][player.x] == target)
			return (true);
		i = 0;
		while (i < 4)
		{
			printf("first stack->content.x: %d, stack->content.y: %d\n", ((t_point *)stack->content)->x, ((t_point *)stack->content)->y);
			next.x = player.x + directions[i][0];
			next.y = player.y + directions[i][1];
			printf("next.x: %d, next.y: %d\n", next.x, next.y);
			printf("first stack->content.x: %d, stack->content.y: %d\n", ((t_point *)stack->content)->x, ((t_point *)stack->content)->y);
			if (is_valid_point(game, next) && !visited[next.y][next.x])
			{
				printf("OK\n");
				ft_lstadd_front(&stack, ft_lstnew(&next));
				visited[next.y][next.x] = 1;
				break ;
			}
			printf("first stack->content.x: %d, stack->content.y: %d\n", ((t_point *)stack->content)->x, ((t_point *)stack->content)->y);
			i++;
		}
		if (i == 4)
		{
			ft_lstremove_front(&stack);
			printf("\nKO\n");
		}
	}
	return (false);
}
