

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
	// t_vec3d	dir;
	
	y = 0;
	scene->mlx = mlx_init(scene->res.width, scene->res.height, "MLX42", true);
	if (!scene->mlx)
		exit(ERROR);
	g_img = mlx_new_image(scene->mlx, scene->res.width, scene->res.height);
	pix = get_corner_pixel(scene);
	// printf("pix: %f %f %f\n", pix.x, pix.y, pix.z);
	while (y < scene->res.height)
	{
		x = 0;
		while (x < scene->res.width)
		{
				// dir = add_vec3d(pix, add_vec3d(multi_vec3d(scene->px, x + 0.5), multi_vec3d(scene->py, scene->res.height - 1 - y + 0.5)));
				// dir = norm_vec3d(dir);
				// mlx_put_pixel(g_img, x, y, old_trace(scene, dir));
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

			// printf("dir %f %f %f\n", dir.x, dir.y, dir.z);