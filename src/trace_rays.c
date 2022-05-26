

#include "miniRT.h"

t_colors	mk_c(int r, int g, int b)
{
	t_colors rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

bool	check_side(t_vec3d n, t_vec3d dir)
{
	if (skalar_vec3d(dir, n) > 0.0)
		return (false);
	return (true);
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

t_vec3d	random_v(int min, int max)
{
	return (norm_vec3d(mk_v(min + (double)rand() / RAND_MAX * (max - min),
		min + (double)rand() / RAND_MAX * (max - min),
		min + (double)rand() / RAND_MAX * (max - min))));
}

t_colors	multi_colors(t_colors one, t_colors two)
{
	t_colors	ret;

	ret.r = (one.r * two.r) / 255;
	ret.g = (one.g * two.g) / 255;
	ret.b = (one.b * two.b) / 255;
	return (ret);
}

t_vec3d get_random_dir(t_vec3d n, t_vec3d p)
{
	t_vec3d	ret;

	ret = sub_vec3d(random_v(-1, 1), add_vec3d(p, n));
	// while (sqrt(len_vec3d(ret)) >= 1)
	// 	ret = sub_vec3d(random_v(-1, 1), add_vec3d(p, n));

	// {
	// 	t_vec3d random = random_v(-1, 1);
		// printf("check %f %f %f\n", random.x, random.y, random.z);

	// 	ret = sub_vec3d(random, add_vec3d(p, n));
	// }
	return (ret);
}

t_vec3d	in_unit_sphere()
{
	t_vec3d	p;

	while (11)
	{
		p = random_v(-1, 1);
		if (sqrt(len_vec3d(p)) >= 1)
			continue ;
		return (p);
	}
}

// t_colors	trace(t_scene *scene, t_list *list, t_ray ray, t_vec3d n, double t, int bounces, int hit, t_colors ret)
// {

// 	return (ret);
// }

t_colors	trace(t_scene *scene, t_ray ray, int bounces)
{
	// t_colors	col;
	t_list		*list;
	double		t;
	t_vec3d		n;
	t_vec3d		p;

	list = scene->list;
	if (!list)
			ray.col = mk_c((ray.dir.x + 1.0) / 2.0 * 255.0, (ray.dir.y + 1.0) / 2.0 * 255.0, (ray.dir.z + 1.0) / 2.0 * 255.0);

	while (list)
	{
		ray.col = mk_c(((t_object *)(list->content))->colors.r,
				((t_object *)(list->content))->colors.g, ((t_object *)(list->content))->colors.b);
		t = find_t(scene, (t_object *)list->content, ray);
		// if (t < 0.0)
			ray.col = mk_c((ray.dir.x + 1.0) / 2.0 * 255.0, (ray.dir.y + 1.0) / 2.0 * 255.0, (ray.dir.z + 1.0) / 2.0 * 255.0);


	printf("check %f %f %d\n", scene->hit, t, ((t_object*)(scene->list->content))->type);

		if (t > 0.0 && t < scene->hit && bounces > 0)//&& if material property == MATTE
		{
			n = norm_vec3d(sub_vec3d(add_vec3d(ray.pos, multi_vec3d(ray.dir, t)), ((t_object *)(list->content))->pos));//center verändert sich?? anderes obj
			ray.pos = add_vec3d(ray.pos, multi_vec3d(ray.dir, t));
			scene->hit = t;
			if (check_side(n, ray.dir) == false)
				return (mk_c(0,0,0));
			p = in_unit_sphere();
			ray.dir = sub_vec3d(get_random_dir(n, p), p);
			// dir = add_vec3d(add_vec3d(n, p), get_random_dir(n, p));
			// p = add_vec3d(p, multi_vec3d(ray.dir, t));
			// t = find_t(scene, (t_object *)list->content, ray);

			// n = norm_vec3d(sub_vec3d(p, pos));//center verändert sich?? anderes obj, andere pos
			ray.col = multi_colors(ray.col, trace(scene, ray, bounces - 1));
		}
		// ret = trace(scene, list, ray, n,
			// t, BOUNCES, HIT, mk_c(((t_object *)(list->content))->colors.r,
			// ((t_object *)(list->content))->colors.g, ((t_object *)(list->content))->colors.b));

		list = list->next;
	}
	return (ray.col);
}

// int	old_trace(t_scene *scene, t_vec3d dir)
// {
// 	int		ret;
// 	double	t;
// 	double	hit;
// 	t_list	*list;
// 	t_vec3d n;

// 	hit = 10000000.0;
// 	ret = col((dir.x + 1.0) / 2.0 * 255.0, (dir.y + 1.0) / 2.0 * 255.0, (dir.z + 1.0) / 2.0 * 255.0);
// 	list = scene->list;
// 	while (list)
// 	{
// 		t = sp_find_t(scene, (t_object *)list->content, dir);
// 		if (t > 0.0 && t < hit)//if t == 0 -> ray "streift" obj.
// 		{
// 			hit = t;
// 			n = norm_vec3d(sub_vec3d(add_vec3d(scene->camera.pos, multi_vec3d(dir, t)), ((t_object *)(list->content))->pos));
// 			ret = col(((t_object *)(list->content))->colors.r, ((t_object *)(list->content))->colors.g, ((t_object *)(list->content))->colors.b);
// 		}
// 		list = list->next;
// 	}
// 	return (ret);
// }
