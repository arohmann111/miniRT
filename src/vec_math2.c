/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:41:24 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 13:55:14 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	return (multi_vec3d(vec, 1 / len_vec3d(vec)));
}

t_vec3d	cross_vec3d(t_vec3d one, t_vec3d two)
{
	t_vec3d	cross;

	cross.x = (one.y * two.z) - (one.z * two.y);
	cross.y = (one.z * two.x) - (one.x * two.z);
	cross.z = (one.x * two.y) - (one.y * two.x);
	return (cross);
}

t_vec3d	mk_v(double x, double y, double z)
{
	t_vec3d	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}
