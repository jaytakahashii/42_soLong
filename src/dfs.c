/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:04 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/08 16:53:08 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int	**init_direction(void)
// {
// 	int	**direction;
// 	int	i;

// 	direction = (int **)malloc(sizeof(int *) * 4);
// 	if (direction == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < 4)
// 	{
// 		direction[i] = (int *)malloc(sizeof(int) * 2);
// 		if (direction[i] == NULL)
// 			return (NULL);
// 		direction = basic_vector(i, direction);
// 		i++;
// 	}
// 	return (direction);
// }

// void	register_next(t_point next, t_dfs *dfs, t_game *game)
// {
// 	t_node	*node;
// 	t_point	tmp;

// 	tmp = next;
// 	node = (t_node *)malloc(sizeof(t_node));
// 	if (!node)
// 		error_and_exit("Malloc error", NULL, game);
// 	node->point = tmp;
// 	node->next = NULL;
// 	push(&dfs->stack, node);
// 	dfs->visited[next.y][next.x] = 1;
// }

// int	register_direction(t_game *game, char target, t_dfs *dfs)
// {
// 	t_point	next;
// 	int		i;

// 	i = 0;
// 	dfs->direction = init_direction();
// 	if (!dfs->direction)
// 		error_and_exit("Malloc error", NULL, game);
// 	while (i < 4)
// 	{
// 		next = (t_point){dfs->current.x + dfs->direction[i][0],
// 			dfs->current.y + dfs->direction[i][1]};
// 		if (is_valid_point(game, next, target) && !dfs->visited[next.y][next.x])
// 		{
// 			register_next(next, dfs, game);
// 			break ;
// 		}
// 		i++;
// 	}
// 	free_int_matrix(dfs->direction, 4);
// 	dfs->direction = NULL;
// 	return (i);
// }

// int	**init_visited(t_game *game)
// {
// 	int	**visited;
// 	int	i;
// 	int	j;

// 	visited = (int **)malloc(sizeof(int *) * game->map.height);
// 	if (visited == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < game->map.height)
// 	{
// 		visited[i] = (int *)malloc(sizeof(int) * game->map.width);
// 		if (visited[i] == NULL)
// 			return (NULL);
// 		j = 0;
// 		while (j < game->map.width)
// 		{
// 			visited[i][j] = 0;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (visited);
// }

// void	dfs_init(t_dfs *dfs)
// {
// 	dfs->stack.top = NULL;
// 	dfs->visited = NULL;
// 	dfs->direction = NULL;
// }

// bool	dfs(t_game *game, t_point player, char target)
// {
// 	t_dfs	dfs;
// 	t_node	*node;
// 	int		i;
// 	bool	found = false;

// 	dfs_init(&dfs);
// 	dfs.visited = init_visited(game);
// 	if (!dfs.visited)
// 		return (false);
// 	node = init_node(player);
// 	if (!node)
// 		return (false);
// 	push(&dfs.stack, node);
// 	free(node);
// 	dfs.visited[player.y][player.x] = 1;
// 	while (dfs.stack.top)
// 	{
// 		dfs.current = dfs.stack.top->point;
// 		if (is_target(game, target, &dfs))
// 		{
// 			found = true;
// 			break ;
// 		}
// 		i = register_direction(game, target, &dfs);
// 		if (i == 4)
// 			node = pop(&dfs.stack);
// 	}
// 	free_stack(&dfs.stack);
// 	free_int_matrix(dfs.visited, game->map.height);
// 	return (false);
// }


int **init_direction(void) {
	int **direction = (int **)malloc(sizeof(int *) * 4);
	if (direction == NULL) return NULL;

	for (int i = 0; i < 4; i++) {
		direction[i] = (int *)malloc(sizeof(int) * 2);
		if (direction[i] == NULL) {
			for (int j = 0; j < i; j++) free(direction[j]);
			free(direction);
			return NULL;
		}
		direction = basic_vector(i, direction);
	}
	return direction;
}

void register_next(t_point next, t_dfs *dfs, t_game *game) {
	t_node *node = (t_node *)malloc(sizeof(t_node));
	if (!node) error_and_exit("Malloc error", NULL, game);
	node->point = next;
	node->next = NULL;
	push(&dfs->stack, node);
	dfs->visited[next.y][next.x] = 1;
}

int register_direction(t_game *game, char target, t_dfs *dfs) {
	t_point next;
	dfs->direction = init_direction();
	if (!dfs->direction) error_and_exit("Malloc error", NULL, game);

	for (int i = 0; i < 4; i++) {
		next = (t_point){dfs->current.x + dfs->direction[i][0], dfs->current.y + dfs->direction[i][1]};
		if (is_valid_point(game, next, target) && !dfs->visited[next.y][next.x]) {
			register_next(next, dfs, game);
			free_int_matrix(dfs->direction, 4);
			dfs->direction = NULL;
			return i;
		}
	}
	free_int_matrix(dfs->direction, 4);
	dfs->direction = NULL;
	return 4;
}

int **init_visited(t_game *game) {
	int **visited = (int **)malloc(sizeof(int *) * game->map.height);
	if (visited == NULL) return NULL;

	for (int i = 0; i < game->map.height; i++) {
		visited[i] = (int *)malloc(sizeof(int) * game->map.width);
		if (visited[i] == NULL) {
			while (i-- > 0) free(visited[i]);
			free(visited);
			return NULL;
		}
		for (int j = 0; j < game->map.width; j++) {
			visited[i][j] = 0;
		}
	}
	return visited;
}

void dfs_init(t_dfs *dfs) {
	dfs->stack.top = NULL;
	dfs->visited = NULL;
	dfs->direction = NULL;
}

bool dfs(t_game *game, t_point player, char target) {
	t_dfs dfs;
	t_node *node;
	int i;
	bool found = false;

	dfs_init(&dfs);
	dfs.visited = init_visited(game);
	if (!dfs.visited) return false;

	node = init_node(player);
	if (!node) {
		free_int_matrix(dfs.visited, game->map.height);
		return false;
	}
	push(&dfs.stack, node);
	dfs.visited[player.y][player.x] = 1;
	while (dfs.stack.top) {
		dfs.current = dfs.stack.top->point;
		if (is_target(game, target, &dfs)) {
			found = true;
			break;
		}
		i = register_direction(game, target, &dfs);
		if (i == 4) {
			node = pop(&dfs.stack);
			free(node);
		}
	}
	free_dfs(&dfs, game);
	return found;
}
