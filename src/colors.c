/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:54:39 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 16:03:59 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	col(int r, int g, int b)
{
	return ((int)r << 24 | (int)g << 16 | (int)b << 8 | (int)(0xFF));
}

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
