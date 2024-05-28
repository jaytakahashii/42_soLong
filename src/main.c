#include <stdio.h>
#include "mlx.h"

typedef struct s_data {
	void	*img;
	void	*picture;
	char	*img_addr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

int	key_hook(int keycode, void *param)
{
	printf("keycode: %d\n", keycode);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int coloer)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = coloer;
}

int	main(int ac, char **av)
{
	void	*mlx_ptr;
	void	*mlx_win;
	t_data	img;

	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, 1920, 1080, "so_long");
	img.img = mlx_new_image(mlx_ptr, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	// put circle of the window (color: blue, radius: 50)
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if ((i - 50) * (i - 50) + (j - 50) * (j - 50) <= 50 * 50)
				my_mlx_pixel_put(&img, 10 + i, 10 + j, 0x0000FF);
		}
	}
	// put traingle of the window (color: red)
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (i + j <= 100)
				my_mlx_pixel_put(&img, 200 + i, 200 + j, 0xFF0000);
		}
	}

	mlx_put_image_to_window(mlx_ptr, mlx_win, img.img, 0, 0);

	// put image textures/soccer_42_42.xpm
	img.picture = mlx_xpm_file_to_image(mlx_ptr, "./textures/soccer_42_42.xpm", &img.bits_per_pixel, &img.line_length);
	mlx_put_image_to_window(mlx_ptr, mlx_win, img.picture, 500, 500);
	mlx_put_image_to_window(mlx_ptr, mlx_win, img.picture, 700, 500);

	mlx_loop(mlx_ptr);
	return (0);
}
