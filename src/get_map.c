/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jay <jay@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:06:08 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/09 12:49:40 by jay              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*get_str(int fd)
{
	char	*str;
	ssize_t	read_bytes;

	str = malloc(sizeof(char) * READ_SIZE);
	if (!str)
		error_and_exit("Malloc error", NULL, NULL);
	read_bytes = read(fd, str, READ_SIZE);
	if (read_bytes < 0)
	{
		free(str);
		error_and_exit("Read error", NULL, NULL);
	}
	if (read_bytes > MAX_READ_SIZE)
	{
		free(str);
		error_and_exit("Map is too big", NULL, NULL);
	}
	str[read_bytes] = '\0';
	return (str);
}

char	**get_map(int fd)
{
	char	*map_str;
	char	**map;

	map_str = get_str(fd);
	map = ft_split(map_str, '\n');
	free(map_str);
	if (!map)
		error_and_exit("Split error", NULL, NULL);
	close(fd);
	return (map);
}
