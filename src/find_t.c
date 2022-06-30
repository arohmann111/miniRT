/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_t.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:53:28 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/30 11:00:43 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	sp_find_t(t_object *sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	dis;
	double	t;

	a = skalar_vec3d(ray.dir, ray.dir);
	b = 2.0 * skalar_vec3d(sub_vec3d(ray.pos, sphere->pos), ray.dir);
	c = skalar_vec3d(sub_vec3d(ray.pos, sphere->pos),
			sub_vec3d(ray.pos, sphere->pos)) - sphere->sp.diameter
		* sphere->sp.diameter / 4.0;
	dis = b * b - 4.0 * a * c;
	if (dis < 0.0)
		return (-1.0);
	t = (-b - sqrt(dis)) / (2.0 * a);
	if (t > 0.0001)
		return (t);
	t = (-b + sqrt(dis)) / (2.0 * a);
	if (t > 0.0001)
		return (t);
	return (-1.0);
}

static t_vec3d	bowl_hit(t_ray ray, t_object *bowl, double t)
{
	return (norm_vec3d(sub_vec3d(add_vec3d(ray.pos, multi_vec3d(ray.dir, t)),
				bowl->pos)));
}

double	bo_find_t(t_object *bowl, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	dis;
	double	t;

	a = skalar_vec3d(ray.dir, ray.dir);
	b = 2.0 * skalar_vec3d(sub_vec3d(ray.pos, bowl->pos), ray.dir);
	c = skalar_vec3d(sub_vec3d(ray.pos, bowl->pos),
			sub_vec3d(ray.pos, bowl->pos)) - bowl->bo.diameter
		* bowl->bo.diameter / 4.0;
	dis = b * b - 4.0 * a * c;
	if (dis < 0.0)
		return (-1.0);
	t = (-b - sqrt(dis)) / (2.0 * a);
	if (t > 0.0001 && skalar_vec3d(bowl->bo.orient, bowl_hit(ray, bowl, t))
		< (cos(bowl->bo.angle * M_PI / 180)))
		return (t);
	t = (-b + sqrt(dis)) / (2.0 * a);
	if (t > 0.0001 && skalar_vec3d(bowl->bo.orient, bowl_hit(ray, bowl, t))
		< (cos(bowl->bo.angle * M_PI / 180)))
		return (t);
	return (-1.0);
}

double	pl_find_t(t_object *plane, t_ray ray)
{
	double	denom;
	t_vec3d	n;
	double	t;

	n = norm_vec3d(plane->pl.orient);
	denom = skalar_vec3d(ray.dir, n);
	t = skalar_vec3d(sub_vec3d(plane->pos, ray.pos), n) / denom;
	if (t < 0.0001 || fabs(denom) < 0.00001)
		return (-1.0);
	else
		return (t);
}

double	circ_find_t(t_object *circle, t_ray ray)
{
	double	denom;
	t_vec3d	n;
	double	t;
	t_vec3d	p;

	n = norm_vec3d(circle->cl.orient);
	denom = skalar_vec3d(ray.dir, n);
	if (fabs(denom) < 0.00001)
		return (-1.0);
	else
	{
		t = (skalar_vec3d(sub_vec3d(circle->pos, ray.pos), n) / denom);
		p = add_vec3d(ray.pos, multi_vec3d(ray.dir, t));
		if (t > 0.0001 && (pow((p.x - circle->pos.x), 2)
				+ pow((p.y - circle->pos.y), 2) + pow((p.z - circle->pos.z), 2))
			< pow((circle->cl.dia / 2), 2))
			return (t);
		else
			return (-1);
	}
}
