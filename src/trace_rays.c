#include "miniRT.h"

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
	if ( dis < 0)
		return (-1.0);
	else
		return (-b - sqrt(dis) / (2.0 * a));
}

int	trace(t_scene *scene, t_vec3d dir)
{
	int		ret;
	double	t;
	double	hit;
	t_list	*list;
	t_vec3d n;

	hit = 100000000000;
	ret = col((dir.x + 1.0) / 2.0 * 255.0, (dir.y + 1.0) / 2.0 * 255.0, (dir.z + 1.0) / 2.0 * 255.0);
	list = scene->list;
	while (list)
	{
		t = sp_find_t(scene, (t_object *)list->content, dir);
		if (t > 0.0 && t < hit)
		{
			//n = norm_vec3d(add_vec3d(scene->camera.pos, sub_vec3d(multi_vec3d(dir, t), ((t_object *)(scene->list->content))->pos)));
			n = norm_vec3d(sub_vec3d(add_vec3d(scene->camera.pos, multi_vec3d(dir, t)), ((t_object *)(list->content))->pos));
			//return (0.5 * col((n.x + 1.0) / 2.0 * 255, (n.y + 1.0) / 2.0 * 255, (n.z + 1.0) / 2.0 * 255));
			ret = col(((t_object *)(list->content))->colors.r, ((t_object *)(list->content))->colors.g, ((t_object *)(list->content))->colors.b);
		}
		list = list->next;
	}
	return (ret);
}
