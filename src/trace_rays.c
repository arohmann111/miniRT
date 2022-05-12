#include "miniRT.h"

int	find_inter(t_scene *scene, t_vec3d dir)
{
	// int	t;
	double a;
	double b;
	double c;
	double dis;
	t_object *sphere;
	
	sphere = scene->list->content;
	a = skalar_vec3d(dir, dir);
	b = 2.0 * skalar_vec3d(sub_vec3d(scene->camera.pos, sphere->pos), dir);
	c = skalar_vec3d(sub_vec3d(scene->camera.pos, sphere->pos),
		sub_vec3d(scene->camera.pos, sphere->pos)) - sphere->sp.diameter * sphere->sp.diameter / 4.0;
	dis = b*b - 4.0*a*c;
	if ( dis > 0)
		return (dis);
	return (0);
}

int	trace(t_scene *scene, t_vec3d dir)
{
	if (find_inter(scene, dir) > 0)
	{
		return (col(230, 200, 150));
	}
	else
		return (col((dir.x + 1.0) / 2.0 * 255.0, (dir.y + 1.0) / 2.0 * 255.0, (dir.z + 1.0) / 2.0 * 255.0));
}
