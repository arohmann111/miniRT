/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 13:57:21 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 14:35:52 by arohmann         ###   ########.fr       */
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

t_colors	col_cut(t_colors c)
{
	if (c.r > 255)
		c.r = 255;
	if (c.g > 255)
		c.g = 255;
	if (c.b > 255)
		c.b = 255;
	return (c);
}

t_colors	mk_c(int r, int g, int b)
{
	t_colors	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}