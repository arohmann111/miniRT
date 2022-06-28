
#include "miniRT.h"

static mlx_image_t *g_img;

int	col(int r, int g, int b)
{
	return ((int)r << 24 | (int)g << 16 | (int)b << 8 | (int)(0xFF));
}

void	close_program(void *data)
{
	t_scene *scene;

	scene = data;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(scene->mlx);
		ft_lstclear(&scene->list, free);
	}
}


int32_t	mlx_stuff(t_scene *scene)
{
	int		x;
	int		y;
	t_vec3d	pix;
	
	y = 0;
	scene->mlx = mlx_init(scene->res.width, scene->res.height, "MLX42", false);
	if (!scene->mlx)
		exit(ERROR);
	g_img = mlx_new_image(scene->mlx, scene->res.width, scene->res.height);
	pix = get_corner_pixel(scene);
	while (y < scene->res.height)
	{
		x = 0;
		while (x < scene->res.width)
		{
				mlx_put_pixel(g_img, x, y, multisample(scene, pix, x, y));
			x++;
		}
		y++;
	}
	mlx_image_to_window(scene->mlx, g_img, 0, 0);   // Adds an image to the render queue.
	mlx_loop_hook(scene->mlx, &close_program, (t_scene*)scene);//loop hook: determines which function should be called during the loop
	mlx_loop(scene->mlx);
	mlx_delete_image(scene->mlx, g_img); // Once the application request an exit, cleanup.
	mlx_terminate(scene->mlx);
	return (0);
}