

#include "miniRT.h"
double	intersect_light(t_scene *scene, t_ray ray);

t_colors	mk_c(int r, int g, int b)
{
	t_colors rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

double	sp_find_t(t_object *sphere, t_ray ray)
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
	if (dis < 0.0)
		return (-1.0);//keine Lösung -> kein Schnittpunkt
	t = (-b - sqrt(dis)) / (2.0 * a);
	if (t > 0.0)
		return (t);
	t = (-b + sqrt(dis)) / (2.0 * a);
	if (t > 0.0)
		return (t);
	return (-1.0);
}

double	pl_find_t(t_object *plane, t_ray ray)
{
	double	denom;
	t_vec3d n;

	n = norm_vec3d(plane->pl.orient);
	denom = skalar_vec3d(ray.dir, n);
	if (fabs(denom) < 0.00001)
		return (-1.0);
	else
		return (skalar_vec3d(sub_vec3d(plane->pos, ray.pos), n) / denom);
}

double	circ_find_t(t_object *circle, t_ray ray)
{
	double	denom;
	t_vec3d n;
	double	res;
	t_vec3d	p;

	n = norm_vec3d(circle->cl.orient);
	denom = skalar_vec3d(ray.dir, n);
	if (fabs(denom) < 0.00001)
		return (-1.0);
	else
	{
		res = (skalar_vec3d(sub_vec3d(circle->pos, ray.pos), n) / denom);
		p = add_vec3d(ray.pos, multi_vec3d(ray.dir, res));
		if ((pow((p.x - circle->pos.x), 2) + pow((p.y - circle->pos.y), 2) + pow((p.z - circle->pos.z), 2)) < pow((circle->cl.dia / 2), 2))
			return (res);
		else
			return (-1);
	}
}

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
	if (t > 0.0 && fabs(cut) < (tube->tb.height / 2.0))
		return (t);
	t = (-b + sqrt(dis)) / (2.0 * a);
	p = add_vec3d(ray.pos, multi_vec3d(ray.dir, t));
	wtf = sub_vec3d(p, tube->pos);
	cut = skalar_vec3d(tube->tb.orient, wtf);
	if (t > 0.0 && fabs(cut) < (tube->tb.height / 2.0))
		return (t);
	return (-1.0);
}

double	find_t(t_object *obj, t_ray ray)
{
	double	t;

	t = -2.0;
	if (obj->type == SPHERE)
	// printf("check\n");
		t = sp_find_t(obj, ray);
	else if (obj->type == PLANE)
		t = pl_find_t(obj, ray);
	else if (obj->type == CIRCLE)
		t = circ_find_t(obj, ray);
	else if (obj->type == TUBE)
		t = tube_find_t(obj, ray);
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

t_colors	multi_col_factor(t_colors col, double factor)
{
	t_colors	ret;

	ret.r = col.r + col.r * factor;
	ret.g = col.g + col.g * factor;
	ret.b = col.b + col.b * factor;
	return (ret);
}

t_colors	simple_multi_col(t_colors col, double factor)
{
	t_colors	ret;

	ret.r = col.r * factor;
	ret.g = col.g * factor;
	ret.b = col.b * factor;
	return (ret);
}

t_colors	check_col_max(t_colors c)
{
	if (c.r > 255)
		c.r = 255;
	if (c.g > 255)
		c.g = 255;
	if (c.b > 255)
		c.b = 255;
	return (c);
}

int	highest_col(t_colors c)
{
	if (c.r <= 255 && c.g <= 255 && c.b <= 255)
		return (255);
	else if (c.r >= c.g && c.r >= c.b)
		return (c.r);
	else if (c.g >= c.r && c.g >= c.b)
		return (c.g);
	else// if (c.b >= c.r && c.b >= c.g)
		return (c.b);
}

t_colors	scale_color(t_colors c)
{
	double	max;
	double percent;

	max = (double)highest_col(c);
	percent = 255.0 / max;
	return(simple_multi_col(c, percent));
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
	t_vec3d		l;
	double		n_l;
	t_light		light;

	light = scene->light;
	ray->pos = add_vec3d(ray->pos, multi_vec3d(ray->dir, scene->hit));
	n = norm_vec3d(sub_vec3d(ray->pos, obj->pos));
	ray->side = OUTSIDE;
	if (skalar_vec3d(n, ray->dir) > 0)
	{
		ray->side = INSIDE;
		n = multi_vec3d(n, -1.0);
	}

	p = add_vec3d(add_vec3d(ray->pos, n), in_unit_sphere());//if lighting is diffuse
	
	ray->dir = norm_vec3d(sub_vec3d(p, ray->pos));

	l = sub_vec3d(light.pos, ray->pos);
	n_l = skalar_vec3d(n, l);
	double x = intersect_light(scene, *ray);
	// if (x == -2)
	// 	ray->col = multi_colors(mk_c(0,0,0), trace(scene, *ray, bounces - 1));
	if (n_l <= 0 || x < 0)
		// ray->col = simple_multi_col(multi_colors(multi_colors(obj->colors, trace(scene, *ray, bounces - 1)), scene->ambiente.colors), scene->ambiente.ratio + scene->ambiente.ratio * 0.24);//??? only use ambient light if no light is met
		ray->col = multi_colors(obj->colors, trace(scene, *ray, bounces - 1));
	else
	{
		// ray->col = multi_colors(ray->col, simple_multi_col(scene->ambiente.colors, 1 / (scene->ambiente.ratio) + 0.5));
		ray->col = multi_col_factor(multi_colors(obj->colors, trace(scene, *ray, bounces - 1)), (1 / pow(x, 2)) * (scene->light.bright * n_l /(len_vec3d(n) * len_vec3d(l))) * 100);
	}
}

void	intersect_plane(t_scene *scene, t_ray *ray, t_object *obj, int bounces)
{
	t_vec3d		n;
	t_vec3d		p;
	t_vec3d		l;
	t_light		light;
	double		n_l;

	light = scene->light;
	ray->pos = add_vec3d(ray->pos, multi_vec3d(ray->dir, scene->hit));
	if (skalar_vec3d(ray->dir, obj->pl.orient) <= 0)
		n = norm_vec3d(obj->pl.orient);
	else
		n =  norm_vec3d(multi_vec3d(obj->pl.orient, -1.0));
	ray->dir = n;
	p = add_vec3d(add_vec3d(ray->pos, n), in_unit_sphere());
	ray->dir = norm_vec3d(sub_vec3d(p, ray->pos));

	l = sub_vec3d(light.pos, ray->pos);
	n_l = skalar_vec3d(n, l);
	double x = intersect_light(scene, *ray);
	// double x = ((light.bright * n_l /(len_vec3d(n) * len_vec3d(l))) * intersect_light(scene, *ray)) / 50;
	if (n_l <= 0 || x < 0)
		// ray->col = simple_multi_col(multi_colors(multi_colors(obj->colors, trace(scene, *ray, bounces - 1)), scene->ambiente.colors), scene->ambiente.ratio + scene->ambiente.ratio * 0.24);//???
		ray->col = multi_colors(obj->colors, trace(scene, *ray, bounces - 1));
	else
		ray->col = multi_col_factor(multi_colors(obj->colors, trace(scene, *ray, bounces - 1)), (1 / pow(x, 2)) * (scene->light.bright * n_l /(len_vec3d(n) * len_vec3d(l))) * 80);
}

void	intersect_tube(t_scene *scene, t_ray *ray, t_object *obj, int bounces)
{
	t_vec3d		n;
	t_vec3d		p;
	t_vec3d		objpos_to_n_intersec;
	t_vec3d		objpos_to_raypos;
	double		s;

	ray->pos = add_vec3d(ray->pos, multi_vec3d(ray->dir, scene->hit));
	objpos_to_raypos = sub_vec3d(ray->pos, obj->pos);
	s = skalar_vec3d(obj->tb.orient, objpos_to_raypos);
	objpos_to_n_intersec = multi_vec3d(obj->tb.orient, s);
	n = norm_vec3d(sub_vec3d(objpos_to_raypos, objpos_to_n_intersec));
	ray->side = OUTSIDE;
	if (skalar_vec3d(n, ray->dir) > 0)
	{
		ray->side = INSIDE;
		n = multi_vec3d(n, -1.0);
	}
	p = add_vec3d(add_vec3d(ray->pos, n), in_unit_sphere());
	ray->dir = norm_vec3d(sub_vec3d(p, ray->pos));
	ray->col = multi_col_factor(multi_colors(obj->colors, trace(scene, *ray, bounces - 1)), intersect_light(scene, *ray) * (scene->light.bright / 100));
}

void	intersect_circle(t_scene *scene, t_ray *ray, t_object *obj, int bounces)
{
	t_vec3d		n;
	t_vec3d		p;

	ray->pos = add_vec3d(ray->pos, multi_vec3d(ray->dir, scene->hit));
	n = norm_vec3d(obj->cl.orient);
	ray->side = OUTSIDE;
	if (skalar_vec3d(n, ray->dir) > 0)
	{
		ray->side = INSIDE;
		n = multi_vec3d(n, -1.0);
	}
	p = add_vec3d(add_vec3d(ray->pos, n), in_unit_sphere());
	ray->dir = norm_vec3d(sub_vec3d(p, ray->pos));
	ray->col = multi_col_factor(multi_colors(obj->colors, trace(scene, *ray, bounces - 1)), intersect_light(scene, *ray) * (scene->light.bright / 100));
}


double	intersect_light(t_scene *scene, t_ray ray)
{
	t_ray	light;
	t_list	*list;
	double	t;

	list = scene->list;
	t = 0.0;
	light = ray;
	light.dir = sub_vec3d(scene->light.pos, light.pos);
	// if (ray.side == INSIDE)
	if (skalar_vec3d(light.dir, ray.dir) < 0)
		return (-2.0);
		// multi_vec3d(light.dir, -1.0);//??? abfangen wenn livht auf innenseite von objekt trifft
	while (list)
	{
		t = find_t((t_object *)list->content, light);
		if (t > 0.0001)
		{
			t_vec3d ray_to_obj = add_vec3d(light.pos, multi_vec3d(light.dir, t));
			if (len_vec3d(ray_to_obj) < len_vec3d(light.dir))
				return (-1.0);
		}
		list = list->next;
	}
	return (len_vec3d(light.dir));
}

t_colors	trace(t_scene *scene, t_ray ray, int bounces)
{
	t_object	*obj;
	t_list		*list;
	double		t;
	t_colors	ambient;

	if (bounces == 0)
		return (mk_c(0,0,0));
	scene->hit = HIT;
	list = scene->list;
	ambient = simple_multi_col(scene->ambiente.colors, scene->ambiente.ratio + 0.5);
	// ray.col = multi_colors(ray.col, ambient);
	while (list)
	{
		t = find_t((t_object *)list->content, ray);
		if (t > 0.00001 && t < scene->hit)
		{
			scene->hit = t;
			obj = (t_object*)(list->content);
		}
		list = list->next;
	}
	if (scene->hit == HIT)
		return (multi_colors(scene->bg.col, ambient));
		// return (simple_multi_col(multi_colors(scene->bg.col, scene->ambiente.colors), scene->ambiente.ratio + scene->ambiente.ratio * 0.24));//ambient light eingerechnet

	//if material property == MATTE

	if (obj->type == SPHERE)
		intersect_sphere(scene, &ray, obj, bounces);
	else if (obj->type == PLANE)
		intersect_plane(scene, &ray, obj, bounces);
	else if (obj->type == TUBE)
		intersect_tube(scene, &ray, obj, bounces);
	else if (obj->type == CIRCLE)
		intersect_circle(scene, &ray, obj, bounces);
	else
		return (obj->colors);

	// ray.col = simple_multi_col(multi_colors(ray.col, scene->ambiente.colors), scene->ambiente.ratio + scene->ambiente.ratio * 0.24);
	return (scale_color(multi_colors(ray.col, ambient)));
}

