

#include "miniRT.h"

t_colors	mk_c(int r, int g, int b)
{
	t_colors rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

double	sp_find_t(t_scene *scene, t_object *sphere, t_vec3d dir)
{
	double a;
	double b;
	double c;
	double dis;
	
	a = skalar_vec3d(dir, dir);
	b = 2.0 * skalar_vec3d(sub_vec3d(scene->camera.pos, sphere->pos), dir);
	c = skalar_vec3d(sub_vec3d(scene->camera.pos, sphere->pos),
		sub_vec3d(scene->camera.pos, sphere->pos)) - sphere->sp.diameter * sphere->sp.diameter / 4.0;
	dis = b*b - 4.0*a*c;
	if (dis < 0)
		return (-1.0);//keine Lösung -> kein Schnittpunkt
	else
		return ((-b - sqrt(dis)) / (2.0 * a));//Mitternachtsformel
}

double	pl_find_t(t_scene *scene, t_object *plane, t_vec3d dir)
{
	double	denom;
	t_vec3d n;

	n = norm_vec3d(plane->pl.orient);
	denom = skalar_vec3d(dir, n);
	if (fabs(denom) < 0.00001)
		return (-1);
	else
		return (skalar_vec3d(sub_vec3d(plane->pos, scene->camera.pos), n) / denom);
}

double	find_t(t_scene *scene, t_object *obj, t_vec3d dir)
{
	double	t;

	t = -2;
	if (obj->type == SPHERE)
		t = sp_find_t(scene, obj, dir);
	else if (obj->type == PLANE)
		t = pl_find_t(scene, obj, dir);
	return (t);
}

t_colors	trace(t_scene *scene, t_vec3d dir)
{
	t_colors	ret;
	double	t;
	double	hit;
	t_list	*list;
	t_vec3d n;

	hit = 10000000.0;
	ret = mk_c((dir.x + 1.0) / 2.0 * 255.0, (dir.y + 1.0) / 2.0 * 255.0, (dir.z + 1.0) / 2.0 * 255.0);
	list = scene->list;
	while (list)
	{
		t = find_t(scene, (t_object *)list->content, dir);
		if (t > 0.0 && t < hit)
		{
			hit = t;
			n = norm_vec3d(sub_vec3d(add_vec3d(scene->camera.pos, multi_vec3d(dir, t)), ((t_object *)(list->content))->pos));
			ret = mk_c(((t_object *)(list->content))->colors.r, ((t_object *)(list->content))->colors.g, ((t_object *)(list->content))->colors.b);
		}
		list = list->next;
	}
	return (ret);
}

int	old_trace(t_scene *scene, t_vec3d dir)
{
	int		ret;
	double	t;
	double	hit;
	t_list	*list;
	t_vec3d n;

	hit = 10000000.0;
	ret = col((dir.x + 1.0) / 2.0 * 255.0, (dir.y + 1.0) / 2.0 * 255.0, (dir.z + 1.0) / 2.0 * 255.0);
	list = scene->list;
	while (list)
	{
		t = sp_find_t(scene, (t_object *)list->content, dir);
		if (t > 0.0 && t < hit)//if t == 0 -> ray "streift" obj.
		{
			hit = t;
			n = norm_vec3d(sub_vec3d(add_vec3d(scene->camera.pos, multi_vec3d(dir, t)), ((t_object *)(list->content))->pos));
			ret = col(((t_object *)(list->content))->colors.r, ((t_object *)(list->content))->colors.g, ((t_object *)(list->content))->colors.b);
		}
		list = list->next;
	}
	return (ret);
}
