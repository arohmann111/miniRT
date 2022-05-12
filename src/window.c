/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:43:21 by afrasch           #+#    #+#             */
/*   Updated: 2022/05/12 16:24:43 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static mlx_image_t *g_img;

int	col(int r, int g, int b)
{
	return ((int)r << 24 | (int)g << 16 | (int)b << 8 | (int)(0xFF));
}


int32_t	mlx_stuff(t_scene *scene)
{
	mlx_t	*mlx;
	int		x;
	int		y;
	t_vec3d	pix;
	t_vec3d	dir;
	
	y = 0;
	mlx = mlx_init(scene->res.width, scene->res.height, "MLX42", true);
	if (!mlx)
		exit(ERROR);
	g_img = mlx_new_image(mlx, scene->res.width, scene->res.height);
	pix = get_corner_pixel(scene);
	printf("pix: %f %f %f\n", pix.x, pix.y, pix.z);
	while (y < scene->res.height)
	{
		x = 0;
		while (x < scene->res.width)
		{
			// if (x % 10 == 0)
				// mlx_put_pixel(g_img, x, y, rand() % RAND_MAX);
			
			dir = add_vec3d(pix, add_vec3d(multi_vec3d(scene->px, x), multi_vec3d(scene->py, scene->res.height - 1 - y)));
			dir = norm_vec3d(dir);
			// printf("dir %f %f %f\n", dir.x, dir.y, dir.z);
			

				// mlx_put_pixel(g_img, x, y, col(0.0, 0.0, (dir.z ) * 255.0));
				// mlx_put_pixel(g_img, x, y, col(0.0, 0.0, (dir.y + 1.0) / 2.0 * 255.0));
				mlx_put_pixel(g_img, x, y, trace(scene, dir));
			// else
			// 	mlx_put_pixel(g_img, x, y, 0xFFFF88FF);

			
			x++;
		}
		y++;
	}
	mlx_image_to_window(mlx, g_img, 0, 0);   // Adds an image to the render queue.
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img); // Once the application request an exit, cleanup.
	mlx_terminate(mlx);
	return (0);
}
