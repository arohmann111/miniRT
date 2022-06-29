/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:52:02 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 14:34:35 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	ft_rand_double(double min, double max)
{
	return (min + (rand() / ((RAND_MAX + 1.0) / (max - min))));
}



t_colors	trace(t_scene *scene, t_ray ray)
{
	t_object	*obj;
	t_list		*list;
	double		t;
	t_colors	ambient;

	scene->hit = HIT;
	list = scene->list;
	ambient = simple_multi_col(scene->ambiente.colors, scene->ambiente.ratio);
	while (list)
	{
		t = find_t((t_object *)list->content, ray);
		if (t > 0.0001 && t < scene->hit)
		{
			scene->hit = t;
			obj = (t_object *)(list->content);
		}
		list = list->next;
	}
	if (scene->hit == HIT)
		return (scale_color(multi_colors(scene->bg.col, ambient)));
	if (obj->type == SPHERE)
		intersect_sphere(scene, &ray, obj);
	else if (obj->type == BOWL)
		intersect_sphere(scene, &ray, obj);
	else if (obj->type == PLANE)
		intersect_plane(scene, &ray, obj);
	else if (obj->type == TUBE)
		intersect_tube(scene, &ray, obj);
	else if (obj->type == CIRCLE)
		intersect_circle(scene, &ray, obj);
	else
		return (obj->colors);
	ray.col = multi_colors(ray.col, ambient);
	return (col_cut(add_col(ray.col, scene->light_c)));
}

//ambient light darf schwarz werden
//bei bounce limit background oder ray.col returnen
//wenn inside object, keine normale umdrehen