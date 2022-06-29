/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:05:42 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 14:34:44 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_colors	get_multi_l(t_scene *scene, t_ray ray, t_vec3d n)
{
	t_colors	uv;
	double		uva;
	t_list		*lights;

	uv = mk_c(0, 0, 0);
	lights = scene->lights;
	while (lights)
	{
		uva = intersect_light(scene, ray, (t_light *)(lights->content), n);
		if (uva > 0.0)
		{
			uv.r += ((t_light *)lights->content)->colors.r * uva;
			uv.g += ((t_light *)lights->content)->colors.g * uva;
			uv.b += ((t_light *)lights->content)->colors.b * uva;
		}
		lights = lights->next;
	}
	return (uv);
}

double	intersect_light(t_scene *scene, t_ray ray, t_light *light, t_vec3d n)
{
	t_ray	l_ray;
	t_list	*list;
	double	n_l;
	double	len;
	double	t;

	l_ray = ray;
	list = scene->list;
	t = 0.0;
	l_ray.dir = sub_vec3d(light->pos, l_ray.pos);
	len = len_vec3d(l_ray.dir);
	l_ray.dir = norm_vec3d(l_ray.dir);
	while (list)
	{
		t = find_t((t_object *)list->content, l_ray);
		if (t > 0.0001 && t < len)
			return (-1.0);
		list = list->next;
	}
	n_l = skalar_vec3d(n, l_ray.dir);
	if (n_l < 0)
		return (-2);
	return (1 / pow(len, 2) * light->bright * 500);
}

t_vec3d	reflection_vec(t_vec3d n, t_ray ray)
{
	t_vec3d	reflection;

	reflection = sub_vec3d(ray.dir, multi_vec3d(n, 2
				* skalar_vec3d(ray.dir, n)));
	return (reflection);
}

t_vec3d	in_unit_sphere(void)
{
	t_vec3d	p;

	while (11)
	{
		p.x = ft_rand_double(-1.0, 1.0);
		p.y = ft_rand_double(-1.0, 1.0);
		p.z = ft_rand_double(-1.0, 1.0);
		if ((p.x * p.x + p.y * p.y + p.z * p.z) > 1.0)
			continue ;
		return (p);
	}
}
