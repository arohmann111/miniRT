/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:54:39 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 13:55:59 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_colors	multi_colors(t_colors one, t_colors two)
{
	t_colors	ret;

	ret.r = (one.r * two.r) / 255;
	ret.g = (one.g * two.g) / 255;
	ret.b = (one.b * two.b) / 255;
	return (ret);
}

t_colors	multi_col_factor(t_colors col, double factor)
{
	t_colors	ret;

	ret.r = col.r + col.r * factor;
	ret.g = col.g + col.g * factor;
	ret.b = col.b + col.b * factor;
	return (ret);
}

t_colors	simple_multi_col(t_colors col, double factor)
{
	t_colors	ret;

	ret.r = col.r * factor;
	ret.g = col.g * factor;
	ret.b = col.b * factor;
	return (ret);
}

t_colors	add_col(t_colors col, t_colors color)
{
	t_colors	ret;

	ret.r = col.r + color.r;
	ret.g = col.g + color.g;
	ret.b = col.b + color.b;
	return (ret);
}
