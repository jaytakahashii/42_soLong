#include "so_long.h"

void	*put_image(t_image img, size_t x, size_t y)
{
	int size;

	size = IMAGE_SIZE;
	img.img = mlx_xpm_file_to_image(img.game->mlx, img.path, &size, &size);
	mlx_put_image_to_window(img.game->mlx, img.game->window, img.img, x, y);
	return (img.img);
}
