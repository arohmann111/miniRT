/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:52:02 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/30 11:00:10 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	ft_rand_double(double min, double max)
{
	return (min + (rand() / ((RAND_MAX + 1.0) / (max - min))));
}

double	find_t(t_object *obj, t_ray ray)
{
	double	t;

	t = -2.0;
	if (obj->type == SPHERE)
		t = sp_find_t(obj, ray);
	else if (obj->type == BOWL)
		t = bo_find_t(obj, ray);
	else if (obj->type == PLANE)
		t = pl_find_t(obj, ray);
	else if (obj->type == CIRCLE)
		t = circ_find_t(obj, ray);
	else if (obj->type == TUBE)
		t = tube_find_t(obj, ray);
	return (t);
}

static void	call_intersection(t_scene *scene, t_ray *ray, t_object *obj)
{
	if (obj->type == SPHERE)
		intersect_sphere(scene, ray, obj);
	else if (obj->type == BOWL)
		intersect_sphere(scene, ray, obj);
	else if (obj->type == PLANE)
		intersect_plane(scene, ray, obj);
	else if (obj->type == TUBE)
		intersect_tube(scene, ray, obj);
	else if (obj->type == CIRCLE)
		intersect_circle(scene, ray, obj);
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
	call_intersection(scene, &ray, obj);
	ray.col = multi_colors(ray.col, ambient);
	return (scale_color(add_col(ray.col, scene->light_c)));
}
