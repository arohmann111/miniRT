/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multisample.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:39:21 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/28 17:45:32 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// must be called once before "srand((unsigned int) time(NULL));"
double	random_d(void)
{
	double	random;

	random = ((double)rand()) / RAND_MAX;
	return (random);
}

int	multisample(t_scene	*scene, t_vec3d pix, int x, int y)
{
	int			i;
	t_colors	color;
	t_colors	rgb;
	t_ray		ray;
	double		arr[SAMPLE];
	t_list		*list;

	list = scene->list;
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
		ray.dir = add_vec3d(pix, add_vec3d(multi_vec3d(scene->px, x + arr[i]), multi_vec3d(scene->py, scene->res.height - 1 - y + arr[i])));
		ray.dir = norm_vec3d(ray.dir);
		ray.pos = scene->camera.pos;
		ray.col = mk_c(0, 0, 0);
		color = trace(scene, ray);
		rgb.r += color.r;
		rgb.g += color.g;
		rgb.b += color.b;
		i++;
	}
	// rgb = simple_multi_col(rgb, (double)1 / (double)SAMPLE);
	// rgb = add_col(simple_multi_col(scene->ambiente.colors, scene->ambiente.ratio), rgb);
	// scale_color(rgb);
	return (col(rgb.r / SAMPLE, rgb.g / SAMPLE, rgb.b / SAMPLE));
}

int	print_error(char *err_msg, int line_cnt, char **arr)
{
	ft_putstr_fd("Error in line ", STDERR_FILENO);
	ft_putnbr_fd(line_cnt, STDERR_FILENO);
	write(STDERR_FILENO, ":\n", 2);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (error_free(ERROR, arr));
}

int	error_free(int error, char **arr)
{
	if (arr != NULL)
	{
		ft_free_array(arr);
		arr = NULL;
	}
	return (error);
}
