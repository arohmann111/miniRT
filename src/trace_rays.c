

#include "miniRT.h"

t_colors	mk_c(int r, int g, int b)
{
	t_colors rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

double	sp_find_t(t_scene *scene, t_object *sphere, t_ray ray)
{
	double a;
	double b;
	double c;
	double dis;
	
	a = skalar_vec3d(ray.dir, ray.dir);
	b = 2.0 * skalar_vec3d(sub_vec3d(ray.pos, sphere->pos), ray.dir);
	c = skalar_vec3d(sub_vec3d(ray.pos, sphere->pos),
		sub_vec3d(ray.pos, sphere->pos)) - sphere->sp.diameter * sphere->sp.diameter / 4.0;
	dis = b*b - 4.0*a*c;
	if (dis < 0)
		return (-1.0);//keine Lösung -> kein Schnittpunkt
	else
		return ((-b - sqrt(dis)) / (2.0 * a));//Mitternachtsformel
	(void)scene;
}

double	pl_find_t(t_scene *scene, t_object *plane, t_ray ray)
{
	double	denom;
	t_vec3d n;

	n = norm_vec3d(plane->pl.orient);
	denom = skalar_vec3d(ray.dir, n);
	if (fabs(denom) < 0.00001)
		return (-1.0);
	else
		return (skalar_vec3d(sub_vec3d(plane->pos, ray.pos), n) / denom);
	(void)scene;
}

double	find_t(t_scene *scene, t_object *obj, t_ray ray)
{
	double	t;

	t = -2;
	if (obj->type == SPHERE)
		t = sp_find_t(scene, obj, ray);
	else if (obj->type == PLANE)
		t = pl_find_t(scene, obj, ray);
	return (t);
	(void)scene;
}

double	ft_rand_double(double min, double max)
{
	return (min + (rand() / ((RAND_MAX + 1.0) / (max - min))));
}

// t_vec3d	random_v(double min, double max)
// {
// 	double	x;

// 	x = (RAND_MAX + 1) / (max - min);
// 	return (mk_v(min + rand() / x,
// 		min + rand() / x,
// 		min + rand() / x));
// }

t_colors	multi_colors(t_colors one, t_colors two)
{
	t_colors	ret;

	ret.r = (one.r * two.r) / 255;
	ret.g = (one.g * two.g) / 255;
	ret.b = (one.b * two.b) / 255;
	return (ret);
}

t_vec3d	in_unit_sphere()
{
	t_vec3d	p;

	while (11)
	{
		p.x = ft_rand_double(-1.0, 1.0);
		p.y = ft_rand_double(-1.0, 1.0);
		p.z = ft_rand_double(-1.0, 1.0);
		if ((p.x*p.x + p.y*p.y + p.z*p.z) > 1.0)
			continue ;
		return (p);
	}
}

t_colors	trace(t_scene *scene, t_ray ray, int bounces)
{
	t_object	*obj;
	t_list		*list;
	double		t;
	t_vec3d		n;
	t_vec3d		p;

	if (bounces == 0)
		return (mk_c(0,0,0));
	scene->hit = HIT;
	list = scene->list;
	while (list)
	{
		t = find_t(scene, (t_object *)list->content, ray);
		if (t > 0.0 && t < scene->hit && t > 0.001)
		{
			scene->hit = t;
			obj = (t_object*)(list->content);
		}
		list = list->next;
	}
	if (scene->hit == HIT)
		return (scene->bg.col);

	//if material property == MATTE
	


	ray.pos = add_vec3d(ray.pos, multi_vec3d(ray.dir, scene->hit));
	n = norm_vec3d(sub_vec3d(ray.pos, obj->pos));//sphere
	ray.dir = n;
	p = add_vec3d(add_vec3d(ray.pos, n), in_unit_sphere());
	ray.dir = norm_vec3d(sub_vec3d(p, ray.pos));

	ray.col = multi_colors(obj->colors, trace(scene, ray, bounces - 1));
	
	return (ray.col);
}

