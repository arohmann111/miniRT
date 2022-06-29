/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:09:02 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 14:15:19 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	intersect_sphere(t_scene *scene, t_ray *ray, t_object *obj)
{
	t_vec3d		n;
	t_vec3d		p;
	double		rand;

	ray->pos = add_vec3d(ray->pos, multi_vec3d(ray->dir, scene->hit));
	n = norm_vec3d(sub_vec3d(ray->pos, obj->pos));
	ray->side = OUTSIDE;
	if (skalar_vec3d(n, ray->dir) > 0)
	{
		ray->side = INSIDE;
		n = multi_vec3d(n, -1.0);
	}
	rand = ft_rand_double(0.0, 1.0);
	if (rand <= obj->matte)
		p = add_vec3d(add_vec3d(ray->pos, n), in_unit_sphere());
	else
		p = add_vec3d(add_vec3d(ray->pos, n), reflection_vec(n, *ray));
	ray->dir = norm_vec3d(sub_vec3d(p, ray->pos));
	scene->light_c = get_multi_l(scene, *ray, n);
	ray->col = obj->colors;
}

void	intersect_plane(t_scene *scene, t_ray *ray, t_object *obj)
{
	t_vec3d		n;
	t_vec3d		p;
	double		rand;

	ray->pos = add_vec3d(ray->pos, multi_vec3d(ray->dir, scene->hit));
	if (skalar_vec3d(ray->dir, obj->pl.orient) <= 0)
		n = norm_vec3d(obj->pl.orient);
	else
		n = norm_vec3d(multi_vec3d(obj->pl.orient, -1.0));
	rand = ft_rand_double(0.0, 1.0);
	if (rand <= obj->matte)
		p = add_vec3d(add_vec3d(ray->pos, n), in_unit_sphere());
	else
		p = add_vec3d(add_vec3d(ray->pos, n), reflection_vec(n, *ray));
	ray->dir = norm_vec3d(sub_vec3d(p, ray->pos));
	scene->light_c = get_multi_l(scene, *ray, n);
	ray->col = obj->colors;
}

void	intersect_tube(t_scene *scene, t_ray *ray, t_object *obj)
{
	t_vec3d		n;
	t_vec3d		p;
	t_vec3d		objpos_to_n_intersec;
	t_vec3d		objpos_to_raypos;
	double		s;
	double		rand;

	ray->pos = add_vec3d(ray->pos, multi_vec3d(ray->dir, scene->hit));
	objpos_to_raypos = sub_vec3d(ray->pos, obj->pos);
	s = skalar_vec3d(obj->tb.orient, objpos_to_raypos);
	objpos_to_n_intersec = multi_vec3d(obj->tb.orient, s);
	n = norm_vec3d(sub_vec3d(objpos_to_raypos, objpos_to_n_intersec));
	ray->side = OUTSIDE;
	if (skalar_vec3d(n, ray->dir) > 0)
	{
		ray->side = INSIDE;
		n = multi_vec3d(n, -1.0);
	}
	rand = ft_rand_double(0.0, 1.0);
	if (rand <= obj->matte)
		p = add_vec3d(add_vec3d(ray->pos, n), in_unit_sphere());
	else
		p = add_vec3d(add_vec3d(ray->pos, n), reflection_vec(n, *ray));
	ray->dir = norm_vec3d(sub_vec3d(p, ray->pos));
	scene->light_c = get_multi_l(scene, *ray, n);
	ray->col = obj->colors;
}

void	intersect_circle(t_scene *scene, t_ray *ray, t_object *obj)
{
	t_vec3d		n;
	t_vec3d		p;
	double		rand;

	ray->pos = add_vec3d(ray->pos, multi_vec3d(ray->dir, scene->hit));
	n = norm_vec3d(obj->cl.orient);
	ray->side = OUTSIDE;
	if (skalar_vec3d(n, ray->dir) > 0)
	{
		ray->side = INSIDE;
		n = multi_vec3d(n, -1.0);
	}
	rand = ft_rand_double(0.0, 1.0);
	if (rand <= obj->matte)
		p = add_vec3d(add_vec3d(ray->pos, n), in_unit_sphere());
	else
		p = add_vec3d(add_vec3d(ray->pos, n), reflection_vec(n, *ray));
	ray->dir = norm_vec3d(sub_vec3d(p, ray->pos));
	scene->light_c = get_multi_l(scene, *ray, n);
	ray->col = obj->colors;
}
