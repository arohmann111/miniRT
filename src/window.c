/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:39:18 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 16:04:24 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	close_program(void *data)
{
	t_scene	*scene;

	scene = data;
	if (mlx_is_key_down(scene->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(scene->mlx);
		ft_lstclear(&scene->list, free);
	}
}

static void	mlx_looping(t_scene *scene, mlx_image_t *g_img)
{
	int			x;
	int			y;
	t_vec3d		pix;

	y = 0;
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
}

void	mlx_stuff(t_scene *scene)
{
	mlx_image_t	*g_img;

	scene->mlx = mlx_init(scene->res.width, scene->res.height, "MLX42", false);
	if (!scene->mlx)
		exit(ERROR);
	g_img = mlx_new_image(scene->mlx, scene->res.width, scene->res.height);
	mlx_looping(scene, g_img);
	mlx_image_to_window(scene->mlx, g_img, 0, 0);
	mlx_loop_hook(scene->mlx, &close_program, (t_scene *)scene);
	mlx_loop(scene->mlx);
	mlx_delete_image(scene->mlx, g_img);
	mlx_terminate(scene->mlx);
}
