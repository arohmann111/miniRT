

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
	double t;
	
	a = skalar_vec3d(dir, dir);
	b = 2.0 * skalar_vec3d(sub_vec3d(scene->camera.pos, sphere->pos), dir);
	c = skalar_vec3d(sub_vec3d(scene->camera.pos, sphere->pos),
		sub_vec3d(scene->camera.pos, sphere->pos)) - sphere->sp.diameter * sphere->sp.diameter / 4.0;
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

void	cy_set_pos(t_object *cy)
{
	cy->cy.pos[0] = add_vec3d(cy->pos, multi_vec3d(cy->cy.orient, cy->cy.height / 2.0));
	cy->cy.pos[1] = add_vec3d(cy->pos, multi_vec3d(cy->cy.orient, cy->cy.height / -2.0));
}

double	circ_find_t(t_scene *scene, t_object *circle, t_vec3d dir, int pos)
{
	double	denom;
	t_vec3d n;
	double	res;
	t_vec3d	p;

	n = norm_vec3d(circle->cy.orient);
	denom = skalar_vec3d(dir, n);
	if (fabs(denom) < 0.00001)
		return (-1);
	else
	{
		res = (skalar_vec3d(sub_vec3d(circle->cy.pos[pos], scene->camera.pos), n) / denom);
		p = add_vec3d(scene->camera.pos, multi_vec3d(dir, res));
		if ((pow((p.x - circle->cy.pos[pos].x), 2) + pow((p.y - circle->cy.pos[pos].y), 2) + pow((p.z - circle->cy.pos[pos].z), 2)) < pow(circle->cy.diameter / 2, 2))
			return (res);
		else
			return (-1);
	}
}

double	tube_find_t(t_scene *scene, t_object *tube, t_vec3d dir)
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

	tmp = cross_vec3d(dir, tube->cy.orient);
	tmp1 = cross_vec3d(sub_vec3d(scene->camera.pos, tube->pos), tube->cy.orient);
	a = skalar_vec3d(tmp, tmp);
	b = 2.0 * skalar_vec3d(tmp, tmp1);
	c = skalar_vec3d(tmp1, tmp1) - pow(tube->cy.diameter / 2.0, 2);
	dis = b * b - 4.0 * a * c;
	if (dis < 0.0)
		return (-1.0);
	t = (-b - sqrt(dis)) / (2.0 * a);
	p = add_vec3d(scene->camera.pos, multi_vec3d(dir, t));
	wtf = add_vec3d(tube->pos, sub_vec3d(p, tube->pos));
	cut = skalar_vec3d(tube->cy.orient, wtf);
	if (t > 0.0 && fabs(cut) < (tube->cy.height / 2.0))
		return (t);
	t = (-b + sqrt(dis)) / (2.0 * a);
	p = add_vec3d(scene->camera.pos, multi_vec3d(dir, t));
	wtf = add_vec3d(tube->pos, sub_vec3d(p, tube->pos));
	cut = skalar_vec3d(tube->cy.orient, wtf);
	if (t > 0.0 && fabs(cut) < (tube->cy.height / 2.0))
		return (t);
	return (-1.0);
}

double	find_t(t_scene *scene, t_object *obj, t_vec3d dir)
{
	double	t;
	// double	t0;
	// double	t1;

	t = -2;
	if (obj->type == SPHERE)
		t = sp_find_t(scene, obj, dir);
	else if (obj->type == PLANE)
		t = pl_find_t(scene, obj, dir);
	// else if (obj->type == CYLINDER)
	// {
	// 	cy_set_pos(obj);
	// 	t0 = circ_find_t(scene, obj, dir, 0);
	// 	t1 = circ_find_t(scene, obj, dir, 1);
	// 	if (t0 == -1.0 && t1 == -1.0)
	// 		return (-1);
	// 	else if (t0 < t1 && t0 > 0.0)
	// 		return (t0);
	// 	else if (t1 < t0 && t1 > 0.0)
	// 		return (t1);
	// 	else if (t0 == -1)
	// 		return (t1);
	// 	else if (t1 == -1)
	// 		return (t0);
	// 	else
	// 		return (-1);
	// }
	else if (obj->type == CYLINDER)
		t = tube_find_t(scene, obj, dir);
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
	// ret = mk_c((dir.x + 1.0) / 2.0 * 255.0, (dir.y + 1.0) / 2.0 * 255.0, (dir.z + 1.0) / 2.0 * 255.0);
	ret = mk_c(100, 100, 100);
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
