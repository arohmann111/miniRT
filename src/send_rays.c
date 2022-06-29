/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:48:38 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 13:56:39 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* w: vec from middle to right edge */
/* q: vec from middle to upper edge */
/* p: vec from origin to left bottom corner // Eckpunkt */
/* px: vec from p in dir x-axis with length of one pixel */
/* py: vec from p in dir y-axis with length of one pixel */
t_vec3d	get_corner_pixel(t_scene *scene)
{
	double	relation;
	t_vec3d	w;
	t_vec3d	q;
	t_vec3d	p;

	relation = (double)scene->res.height / (double)scene->res.width;
	if (fabs(scene->camera.orient.y) > 0.9)
		w = cross_vec3d(scene->camera.orient, mk_v(0.0, 0.0, 1.0));
	else
		w = cross_vec3d(scene->camera.orient, mk_v(0.0, 1.0, 0.0));
	q = cross_vec3d(w, scene->camera.orient);
	w = norm_vec3d(w);
	w = multi_vec3d(w, tan((scene->camera.fov / 2.0) / 180 * M_PI));
	q = norm_vec3d(q);
	q = multi_vec3d(q, relation * tan((scene->camera.fov / 2.0) / 180 * M_PI));
	p = sub_vec3d(add_vec3d(scene->camera.pos, scene->camera.orient),
			add_vec3d(w, q));
	scene->px = div_vec3d(w, (0.5 * scene->res.width));
	scene->py = div_vec3d(q, (0.5 * scene->res.height));
	return (sub_vec3d(p, scene->camera.pos));
}
