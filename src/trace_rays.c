

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
	double t;
	
	a = skalar_vec3d(ray.dir, ray.dir);
	b = 2.0 * skalar_vec3d(sub_vec3d(ray.pos, sphere->pos), ray.dir);
	c = skalar_vec3d(sub_vec3d(ray.pos, sphere->pos),
		sub_vec3d(ray.pos, sphere->pos)) - sphere->sp.diameter * sphere->sp.diameter / 4.0;
	dis = b * b - 4.0 * a * c;
	if (dis < 0)
		return (-1.0);//keine Lösung -> kein Schnittpunkt
	t = (-b - sqrt(dis)) / (2.0 * a);
	if (t > 0.0)
		return (t);
	t = (-b + sqrt(dis)) / (2.0 * a);
	if (t > 0.0)
		return (t);
	return (-1.0);
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


// void	cy_set_pos(t_object *cy)
// {
// 	cy->cy.pos[0] = add_vec3d(cy->pos, multi_vec3d(cy->cy.orient, cy->cy.height / 2.0));
// 	cy->cy.pos[1] = add_vec3d(cy->pos, multi_vec3d(cy->cy.orient, cy->cy.height / -2.0));
// }

double	circ_find_t(t_scene *scene, t_object *circle, t_ray ray)
{
	double	denom;
	t_vec3d n;
	double	res;
	t_vec3d	p;

	n = norm_vec3d(circle->cl.orient);
	denom = skalar_vec3d(ray.dir, n);
	if (fabs(denom) < 0.00001)
		return (-1);
	else
	{
		res = (skalar_vec3d(sub_vec3d(circle->pos, ray.pos), n) / denom);
		p = add_vec3d(ray.pos, multi_vec3d(ray.dir, res));
		if ((pow((p.x - circle->pos.x), 2) + pow((p.y - circle->pos.y), 2) + pow((p.z - circle->pos.z), 2)) < pow(circle->cl.dia / 2, 2))
			return (res);
		else
			return (-1);
	}
}

double	tube_find_t(t_scene *scene, t_object *tube, t_ray ray)
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
	wtf = add_vec3d(tube->pos, sub_vec3d(p, tube->pos));
	cut = skalar_vec3d(tube->tb.orient, wtf);
	if (t > 0.0 && fabs(cut) < (tube->tb.height / 2.0))
		return (t);
	t = (-b + sqrt(dis)) / (2.0 * a);
	p = add_vec3d(ray.pos, multi_vec3d(ray.dir, t));
	wtf = add_vec3d(tube->pos, sub_vec3d(p, tube->pos));
	cut = skalar_vec3d(tube->tb.orient, wtf);
	if (t > 0.0 && fabs(cut) < (tube->tb.height / 2.0))
		return (t);
	return (-1.0);
}

double	find_t(t_scene *scene, t_object *obj, t_ray ray)
{
	double	t;

	t = -2;
	if (obj->type == SPHERE)
		t = sp_find_t(scene, obj, ray);
	else if (obj->type == PLANE)
		t = pl_find_t(scene, obj, ray);
	else if (obj->type == CIRCLE)
		t = circ_find_t(scene, obj, ray);
	else if (obj->type == TUBE)
		t = tube_find_t(scene, obj, ray);
	return (t);
}

double	ft_rand_double(double min, double max)
{
	return (min + (rand() / ((RAND_MAX + 1.0) / (max - min))));
}

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

void	intersect_sphere(t_scene *scene, t_ray *ray, t_object *obj, int bounces)
{
	t_vec3d		n;
	t_vec3d		p;

	ray->pos = add_vec3d(ray->pos, multi_vec3d(ray->dir, scene->hit));
	n = norm_vec3d(sub_vec3d(ray->pos, obj->pos));
	ray->dir = n;
	p = add_vec3d(add_vec3d(ray->pos, n), in_unit_sphere());
	ray->dir = norm_vec3d(sub_vec3d(p, ray->pos));
	ray->col = multi_colors(obj->colors, trace(scene, *ray, bounces - 1));
}

void	intersect_plane(t_scene *scene, t_ray *ray, t_object *obj, int bounces)
{
	t_vec3d		n;
	t_vec3d		p;

	ray->pos = add_vec3d(ray->pos, multi_vec3d(ray->dir, scene->hit));
	if (skalar_vec3d(ray->dir, obj->pl.orient) <= 0)
		n = norm_vec3d(obj->pl.orient);
	else
		n =  norm_vec3d(multi_vec3d(obj->pl.orient, -1.0));
	ray->dir = n;
	p = add_vec3d(add_vec3d(ray->pos, n), in_unit_sphere());
	ray->dir = norm_vec3d(sub_vec3d(p, ray->pos));
	ray->col = multi_colors(obj->colors, trace(scene, *ray, bounces - 1));
}

t_colors	trace(t_scene *scene, t_ray ray, int bounces)
{
	t_object	*obj;
	t_list		*list;
	double		t;

	if (bounces == 0)
		return (mk_c(0,0,0));
	scene->hit = HIT;
	list = scene->list;
	while (list)
	{
		t = find_t(scene, (t_object *)list->content, ray);
		if (t > 0.0 && t < scene->hit && t > 0.00001)
		{
			scene->hit = t;
			obj = (t_object*)(list->content);
		}
		list = list->next;
	}
	if (scene->hit == HIT)
		return (scene->bg.col);

	//if material property == MATTE
	//if obj == SPHERE
	
	if (obj->type == SPHERE)
		intersect_sphere(scene, &ray, obj, bounces);
	else if (obj->type == PLANE)
		intersect_plane(scene, &ray, obj, bounces);
	else
		return (obj->colors);
	return (ray.col);
}

