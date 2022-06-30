/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:40:29 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 13:42:04 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
