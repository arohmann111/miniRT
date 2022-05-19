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
	int i;
	t_colors colo;
	t_colors rgb;
	t_vec3d dir;
	double arr[50];

	i = 0;
	rgb.r = 0;
	rgb.g = 0;
	rgb.b = 0;
	srand((unsigned int) time(NULL));
	while (i < 50)
	{
		arr[i] = random_d();
		i++;
	}
	i = 0;
	while (i < 50)
	{
		dir = add_vec3d(pix, add_vec3d(multi_vec3d(scene->px, x + arr[i]), multi_vec3d(scene->py, scene->res.height - 1 - y + arr[i])));
		dir = norm_vec3d(dir);
		colo = trace(scene, dir);
		rgb.r += colo.r;
		rgb.g += colo.g;
		rgb.b += colo.b;
		i++;
	}
	return (col(rgb.r/50.0, rgb.g/50.0, rgb.b/50.0));
}
