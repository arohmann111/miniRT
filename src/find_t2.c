/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_t2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:07:52 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 19:08:07 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"



double	tube_find_t(t_object *tube, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	dis;
	double	cut;
	double	t;
	t_vec3d	tmp;
	t_vec3d	tmp1;
	t_vec3d	wtf;
	t_vec3d	p;

	tmp = cross_vec3d(ray.dir, tube->tb.orient);
	tmp1 = cross_vec3d(sub_vec3d(ray.pos, tube->pos), tube->tb.orient);
	a = skalar_vec3d(tmp, tmp);
	b = 2.0 * skalar_vec3d(tmp, tmp1);
	c = skalar_vec3d(tmp1, tmp1) - pow(tube->tb.diameter / 2.0, 2);
	
	dis = b * b - 4.0 * a * c;
	if (dis < 0.0)
		return (-1.0);

	t = (-b - sqrt(dis)) / (2.0 * a);

	p = add_vec3d(ray.pos, multi_vec3d(ray.dir, t));
	wtf = sub_vec3d(p, tube->pos);
	cut = skalar_vec3d(tube->tb.orient, wtf);
	if (t > 0.0001 && fabs(cut) < (tube->tb.height / 2.0))
		return (t);

	t = (-b + sqrt(dis)) / (2.0 * a);

	p = add_vec3d(ray.pos, multi_vec3d(ray.dir, t));
	wtf = sub_vec3d(p, tube->pos);
	cut = skalar_vec3d(tube->tb.orient, wtf);
	if (t > 0.0001 && fabs(cut) < (tube->tb.height / 2.0))
		return (t);
	return (-1.0);
}
