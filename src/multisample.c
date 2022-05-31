#include "miniRT.h"

// must be called once before "srand((unsigned int) time(NULL));"
double random_d()
{
	double random;

	random = ((double)rand()) / RAND_MAX;
	return (random);
}

int	multisample(t_scene	*scene, t_vec3d pix, int x, int y)
{
	int			i;
	t_colors	color;
	t_colors	rgb;
	t_ray		ray;
	double		arr[SAMPLE];
	t_list *list;

	list = scene->list;

	i = 0;
	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;
	// srand((unsigned int) time(NULL));
	while (i < SAMPLE)
	{
		arr[i] = random_d();
		i++;
	}
	i = 0;
	while (i < SAMPLE)
	{
		ray.dir = add_vec3d(pix, add_vec3d(multi_vec3d(scene->px, x + arr[i]), multi_vec3d(scene->py, scene->res.height - 1 - y + arr[i])));
		ray.dir = norm_vec3d(ray.dir);
		ray.pos = scene->camera.pos;
		ray.col = mk_c(0, 0, 0);
		color = trace(scene, ray, BOUNCES);
		rgb.r += color.r;
		rgb.g += color.g;
		rgb.b += color.b;
		i++;
	}
	return (col(rgb.r/SAMPLE, rgb.g/SAMPLE, rgb.b/SAMPLE));
}
