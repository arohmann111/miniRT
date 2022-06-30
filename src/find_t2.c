/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_t2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:07:52 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/30 10:57:36 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	tube_t2(t_object *tube, t_ray ray, double t)
{
	t_vec3d	wtf;
	t_vec3d	p;
	double	cut;

	p = add_vec3d(ray.pos, multi_vec3d(ray.dir, t));
	wtf = sub_vec3d(p, tube->pos);
	cut = skalar_vec3d(tube->tb.orient, wtf);
	return (cut);
}

double	tube_find_t(t_object *tube, t_ray ray)
{
	double	m[3];
	double	dis;
	double	t[2];
	t_vec3d	tmp;
	t_vec3d	tmp1;

	tmp = cross_vec3d(ray.dir, tube->tb.orient);
	tmp1 = cross_vec3d(sub_vec3d(ray.pos, tube->pos), tube->tb.orient);
	m[0] = skalar_vec3d(tmp, tmp);
	m[1] = 2.0 * skalar_vec3d(tmp, tmp1);
	m[2] = skalar_vec3d(tmp1, tmp1) - pow(tube->tb.diameter / 2.0, 2);
	dis = m[1] * m[1] - 4.0 * m[0] * m[2];
	if (dis < 0.0)
		return (-1.0);
	t[0] = (-m[1] - sqrt(dis)) / (2.0 * m[0]);
	t[1] = tube_t2(tube, ray, t[0]);
	if (t[0] > 0.0001 && fabs(t[1]) < (tube->tb.height / 2.0))
		return (t[0]);
	t[0] = (-m[1] + sqrt(dis)) / (2.0 * m[0]);
	t[1] = tube_t2(tube, ray, t[0]);
	if (t[0] > 0.0001 && fabs(t[1]) < (tube->tb.height / 2.0))
		return (t[0]);
	return (-1.0);
}
