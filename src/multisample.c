/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multisample.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:25:11 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 19:00:48 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	random_d(void)
{
	double	random;

	random = ((double)rand()) / RAND_MAX;
	return (random);
}

int	multisample(t_scene	*scene, t_vec3d pix, int x, int y)
{
	int			i;
	t_colors	rgb;
	t_ray		ray;
	double		arr[SAMPLE];

	i = 0;
	rgb = mk_c(0, 0, 0);
	while (i < SAMPLE)
	{
		arr[i] = random_d();
		i++;
	}
	i = 0;
	while (i < SAMPLE)
	{
		ray.dir = add_vec3d(pix, add_vec3d(multi_vec3d(scene->px, x + arr[i]),
					multi_vec3d(scene->py,
						scene->res.height - 1 - y + arr[i])));
		ray.dir = norm_vec3d(ray.dir);
		ray.pos = scene->camera.pos;
		ray.col = mk_c(0, 0, 0);
		rgb = add_col(rgb, trace(scene, ray));
		i++;
	}
	return (col(rgb.r / SAMPLE, rgb.g / SAMPLE, rgb.b / SAMPLE));
}
