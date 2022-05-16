

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
	if (dis < 0)
		return (ERROR);//keine Lösung -> kein Schnittpunkt
	else
		return (-b - sqrt(dis) / (2.0 * a));//Mitternachtsformel
}

int	trace(t_scene *scene, t_vec3d dir)
{
	int t;//für v = campos + t*camdir
	t_vec3d n;//normale

	t = find_inter(scene, dir);
	if ( t > 0.0)//Punkt befindet sich im Blickfeld
	{
		// n = norm_vec3d(add_vec3d(scene->camera.pos, sub_vec3d(multi_vec3d(dir, t), ((t_object *)(scene->list->content))->pos)));
		n = norm_vec3d(sub_vec3d(add_vec3d(scene->camera.pos, multi_vec3d(dir, t)), ((t_object *)(scene->list->content))->pos));
		//
		return (col((n.x - 1.0) / -2.0 * 255.0, (n.y - 1.0) / -2.0 * 255.0, (n.z - 1.0) / -2.0 * 255.0));
	}
	return (col((dir.x + 1.0) / 2.0 * 255.0, (dir.y + 1.0) / 2.0 * 255.0, (dir.z + 1.0) / 2.0 * 255.0));
}
