/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:45:28 by arohmann          #+#    #+#             */
/*   Updated: 2022/05/09 16:56:41 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3d	add_vec3(t_vec3d one, t_vec3d two)
{
	t_vec3d	add;

	add.x = one.x + two.x;
	add.y = one.y + two.y;
	add.z = one.z + two.z;
	return (add);
}

t_vec3d	sub_vec3(t_vec3d one, t_vec3d two)
{
	t_vec3d	sub;

	sub.x = one.x - two.x;
	sub.y = one.y - two.y;
	sub.z = one.z - two.z;
	return (sub);
}

t_vec3d	multi_vec3(t_vec3d vec, double t)
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

t_vec3d	div_vec3(t_vec3d vec, double t)
{
	t_vec3d	div;

	div.x = vec.x / t;
	div.y = vec.y / t;
	div.z = vec.z / t;
	return (div);
}

t_vec3d	norm_vec3d(t_vec3d vec)
{
	double	len;
	t_vec3d	norm;

	len = len_vec3d(vec);
	norm = div_vec3(vec, len);
	return (norm);
}

t_vec3d	cross_vec3d(t_vec3d one, t_vec3d two)
{
	t_vec3d	cross;

	cross.x = (one.y * two.z) - (one.z * two.y);
	cross.y = (one.z * two.x) - (one.x * two.z);
	cross.z = (one.x * two.y) - (one.y * two.x);
	return (cross);
}
