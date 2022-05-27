

#include "miniRT.h"

t_vec3d	add_vec3d(t_vec3d one, t_vec3d two)
{
	t_vec3d	add;

	add.x = one.x + two.x;
	add.y = one.y + two.y;
	add.z = one.z + two.z;
	return (add);
}

t_vec3d	sub_vec3d(t_vec3d one, t_vec3d two)
{
	t_vec3d	sub;

	sub.x = one.x - two.x;
	sub.y = one.y - two.y;
	sub.z = one.z - two.z;
	return (sub);
}

t_vec3d	multi_vec3d(t_vec3d vec, double t)
{
	t_vec3d	multi;

	multi.x = vec.x * t;
	multi.y = vec.y * t;
	multi.z = vec.z * t;
	return (multi);
}

double	skalar_vec3d(t_vec3d one, t_vec3d two)
{
	double	res;

	res = (one.x * two.x) + (one.y * two.y) + (one.z * two.z);
	return (res);
}

double	len_vec3d(t_vec3d vec)
{
	double	res;

	res = sqrt(skalar_vec3d(vec, vec));
	return (res);
}

t_vec3d	div_vec3d(t_vec3d vec, double t)
{
	t_vec3d	div;

	div.x = vec.x / t;
	div.y = vec.y / t;
	div.z = vec.z / t;
	return (div);
}

t_vec3d	norm_vec3d(t_vec3d vec)
{
	// double	len;
	// t_vec3d	norm;

	// len = len_vec3d(vec);
	// norm = div_vec3d(vec, len);
	// return (norm);
	return (multi_vec3d(vec, 1 / len_vec3d(vec)));
}

t_vec3d	cross_vec3d(t_vec3d one, t_vec3d two)
{
	t_vec3d	cross;

	cross.x = (one.y * two.z) - (one.z * two.y);
	cross.y = (one.z * two.x) - (one.x * two.z);
	cross.z = (one.x * two.y) - (one.y * two.x);
	return (cross);//parallel vecs -> 0, else orthogonal vec
}
