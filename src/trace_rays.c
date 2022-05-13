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
	if ( dis < 0)
		return (-1.0);
	else
		return (dis);
}

int	trace(t_scene *scene, t_vec3d dir)
{
	double t;
	t_vec3d n;
	// t_vec3d u_dir;

	t = find_inter(scene, dir);
	if ( t > 0.0)
	{
		n = norm_vec3d(sub_vec3d(multi_vec3d(dir, t), mk_v(0, 0, -1)));
		return (0.5 * col(n.x + 1, n.y + 1, n.z + 1));
	}
	// u_dir = norm_vec3d(dir);
	// t = 0.5 * (u_dir.y + 1.0);
	// return ((1.0 - t) * col(1, 1, 1) + t * col(0, 1, 1));
	return (col((dir.x + 1.0) / 2.0 * 255.0, (dir.y + 1.0) / 2.0 * 255.0, (dir.z + 1.0) / 2.0 * 255.0));
}
