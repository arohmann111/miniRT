/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:57:21 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/30 14:20:40 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_colors	check_col_max(t_colors c)
{
	if (c.r > 255)
		c.r = 255;
	if (c.g > 255)
		c.g = 255;
	if (c.b > 255)
		c.b = 255;
	return (c);
}

int	highest_col(t_colors c)
{
	if (c.r <= 255 && c.g <= 255 && c.b <= 255)
		return (255);
	else if (c.r >= c.g && c.r >= c.b)
		return (c.r);
	else if (c.g >= c.r && c.g >= c.b)
		return (c.g);
	else
		return (c.b);
}

t_colors	scale_color(t_colors c)
{
	double	max;
	double	percent;

	max = (double)highest_col(c);
	percent = 255.0 / max;
	return (simple_multi_col(c, percent));
}

t_colors	mk_c(int r, int g, int b)
{
	t_colors	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}
