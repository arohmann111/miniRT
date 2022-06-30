/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_items.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 16:58:07 by afrasch           #+#    #+#             */
/*   Updated: 2022/06/30 11:58:46 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	convert_colors(char **colors, t_colors *c, int line_cnt)
{
	int		i;
	int		rgb[3];
	int		error;

	i = 0;
	error = 0;
	while (i < 3)
	{
		rgb[i] = ft_atoi(colors[i], &error);
		if (error == ERROR)
			return (print_error("Color can't be converted", line_cnt, NULL));
		if (check_range(0.0, 255.0, (double)rgb[i]) == false)
			return (print_error("Color is not in range [0-255]",
					line_cnt, NULL));
		i++;
	}
	c->r = rgb[0];
	c->g = rgb[1];
	c->b = rgb[2];
	return (0);
}

int	get_colors(t_colors *c, char *split_str, int line_cnt)
{
	char	**colors;

	colors = ft_split(split_str, ',');
	if (!colors)
		return (print_error("Split failed", line_cnt, colors));
	if (arrlen(colors) != 3)
		return (print_error("Wrong number of colors", line_cnt, colors));
	if (convert_colors(colors, c, line_cnt) == ERROR)
		return (error_free(ERROR, colors));
	ft_free_array(colors);
	return (0);
}

static int	convert_coordinates(char **vector, double xyz[3],
	int line_cnt, int type)
{
	int		i;
	int		error;

	i = 0;
	error = 0;
	while (i < 3)
	{
		xyz[i] = ft_atod(vector[i], &error);
		if (error == ERROR)
			return (print_error("Vector can't be converted",
					line_cnt, NULL));
		if (type == COORDINATES)
		{
			if (check_range(-500.0, 500.0, xyz[i]) == false)
				return (print_error("Coordinate vec is not in range [-500,500]",
						line_cnt, NULL));
		}
		else if (type == ORIENTATION)
			if (check_range(-1000.0, 1000.0, xyz[i]) == false)
				return (print_error("Dir vector is not in range [-1000,1000]",
						line_cnt, NULL));
		i++;
	}
	return (0);
}

int	get_vector(t_vec3d *v, char *split_str, int type, int line_cnt)
{
	char	**vector;
	double	xyz[3];

	vector = ft_split(split_str, ',');
	if (!vector)
		return (print_error("Split failed", line_cnt, vector));
	if (arrlen(vector) != 3)
		return (print_error("Wrong number of vector coordinates",
				line_cnt, vector));
	if (convert_coordinates(vector, xyz, line_cnt, type) == ERROR)
		return (error_free(ERROR, vector));
	v->x = xyz[0];
	v->y = xyz[1];
	v->z = xyz[2];
	if (type == ORIENTATION)
		*v = norm_vec3d(*v);
	ft_free_array(vector);
	return (0);
}
