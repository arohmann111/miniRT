/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:31:06 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 11:52:47 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_tube(t_scene *scene, char **split, int line_cnt)
{
	t_list	*new;
	double	dia;
	double	height;
	int		error;

	error = 0;
	if (arrlen(split) != 7)
		return (print_error("Wrong tube input", line_cnt, split));
	new = get_new_obj(TUBE);
	if (!new)
		return (print_error("Tube object can't be allocated", line_cnt, NULL));
	ft_lstadd_back(&scene->list, new);
	if (get_vector(&((t_object *)new->content)->pos, split[1],
			COORDINATES, line_cnt) == ERROR)
		return (error_free(ERROR, NULL));
	if (get_vector(&((t_object *)new->content)->tb.orient, split[2],
			ORIENTATION, line_cnt) == ERROR)
		return (error_free(ERROR, NULL));
	dia = ft_atod(split[3], &error);
	if (error == ERROR)
		return (print_error("Tube diameter can't be converted",
				line_cnt, NULL));
	((t_object *)new->content)->tb.diameter = dia;
	height = ft_atod(split[4], &error);
	if (error == ERROR)
		return (print_error("Tube height can't be converted", line_cnt, NULL));
	((t_object *)new->content)->tb.height = height;
	if (get_colors(&((t_object *)new->content)->colors, split[5],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_material((t_object *)new->content, split[6], line_cnt) == ERROR)
		return (error_free(ERROR, split));
	return (0);
}

int	get_circle(t_scene *scene, char **split, int line_cnt)
{
	t_list	*new;
	double	dia;
	int		error;

	error = 0;
	if (arrlen(split) != 6)
		return (print_error("Wrong circle input", line_cnt, split));
	new = get_new_obj(CIRCLE);
	if (!new)
		return (print_error("Circle object can't be allocated",
				line_cnt, split));
	ft_lstadd_back(&scene->list, new);
	if (get_vector(&((t_object *)new->content)->pos, split[1],
			COORDINATES, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_vector(&((t_object *)new->content)->cl.orient, split[2],
			ORIENTATION, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	dia = ft_atod(split[3], &error);
	if (error == ERROR)
		return (print_error("Circle diameter can't be converted",
				line_cnt, split));
	((t_object *)new->content)->cl.dia = dia;
	if (get_colors(&((t_object *)new->content)->colors, split[4],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_material((t_object *)new->content, split[5], line_cnt) == ERROR)
		return (error_free(ERROR, split));
	ft_free_array(split);
	return (0);
}

int	get_cy_circle(t_scene *scene, char **split, int line_cnt, t_vec3d pos)
{
	t_list	*new;
	double	dia;
	int		error;

	error = 0;
	if (arrlen(split) != 7)
		return (print_error("Wrong circle input", line_cnt, split));
	new = get_new_obj(CIRCLE);
	if (!new)
		return (print_error("Circle object can't be allocated",
				line_cnt, NULL));
	ft_lstadd_back(&scene->list, new);
	if (check_range(-500.0, 500.0, pos.x) == false
		|| check_range(-500.0, 500.0, pos.y) == false
		|| check_range(-500.0, 500.0, pos.z) == false)
		return (print_error("Coordinate vector is not in range [-500.0,500.0]",
				line_cnt, NULL));
	((t_object *)new->content)->pos = pos;
	if (get_vector(&((t_object *)new->content)->cl.orient, split[2],
			ORIENTATION, line_cnt) == ERROR)
		return (ERROR);
	dia = ft_atod(split[3], &error);
	if (error == ERROR)
		return (print_error("Circle diameter can't be converted",
				line_cnt, NULL));
	((t_object *)new->content)->cl.dia = dia;
	if (get_colors(&((t_object *)new->content)->colors, split[5],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_material((t_object *)new->content, split[6], line_cnt) == ERROR)
		return (error_free(ERROR, split));
	return (0);
}

int	get_cylinder(t_scene *scene, char **split, int line_cnt)
{
	t_vec3d	vec;
	t_vec3d	dir;
	t_vec3d	pos;
	double	height;
	int		error;

	error = 0;
	if (get_tube(scene, split, line_cnt) == ERROR)
		return (ERROR);
	if (get_vector(&vec, split[1], COORDINATES, line_cnt) == ERROR)
		return ((ERROR));
	if (get_vector(&dir, split[2], ORIENTATION, line_cnt) == ERROR)
		return (ERROR);
	height = ft_atod(split[4], &error);
	if (error == ERROR)
		return (print_error("Cylinder height can't be converted",
				line_cnt, NULL));
	pos = add_vec3d(vec, multi_vec3d(dir, height / 2.0));
	if (get_cy_circle(scene, split, line_cnt, pos) == ERROR)
		return (ERROR);
	pos = add_vec3d(vec, multi_vec3d(dir, height / -2.0));
	if (get_cy_circle(scene, split, line_cnt, pos) == ERROR)
		return (ERROR);
	ft_free_array(split);
	return (0);
}
