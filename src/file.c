/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtakahas <jtakahas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:49:29 by jtakahas          #+#    #+#             */
/*   Updated: 2024/06/04 17:49:30 by jtakahas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	diff_extension(char *file_name, char *ext)
{
	int	file_len;
	int	ext_len;

	file_len = ft_strlen(file_name);
	ext_len = ft_strlen(ext);
	if (file_len < ext_len)
		return (false);
	while (ext_len > 0)
	{
		if (file_name[file_len - 1] != ext[ext_len - 1])
			return (false);
		file_len--;
		ext_len--;
	}
	return (true);
}

int	get_fd(char *map_file_path, t_game *game)
{
	int	fd;

	fd = open(map_file_path, O_RDONLY);
	if (fd < 0)
		error_and_exit("Invalid map file", "failed to open map file", game);
	if (diff_extension(map_file_path, ".ber") == false)
		error_and_exit("Invalid map file", "file extension must be .ber", game);
	return (fd);
}
