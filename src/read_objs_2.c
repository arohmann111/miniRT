/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_objs_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:31:06 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 18:43:37 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	get_tube_2(t_list *new, char **split, int line_cnt)
{
	int		error;

	error = 0;
	((t_object *)new->content)->tb.diameter = ft_atod(split[3], &error);
	if (error == ERROR)
		return (print_error("Tube diameter can't be converted",
				line_cnt, NULL));
	error = 0;
	((t_object *)new->content)->tb.height = ft_atod(split[4], &error);
	if (error == ERROR)
		return (print_error("Tube height can't be converted", line_cnt, NULL));
	if (get_colors(&((t_object *)new->content)->colors, split[5],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	return (0);
}

int	get_tube(t_scene *scene, char **split, int line_cnt)
{
	t_list	*new;

	if (arrlen(split) != 6)
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
	if (get_tube_2(new, split, line_cnt) == ERROR)
		return (ERROR);
	return (0);
}

int	get_circle(t_scene *scene, char **split, int line_cnt)
{
	t_list	*new;
	int		error;

	error = 0;
	if (arrlen(split) != 5)
		return (print_error("Wrong circle input", line_cnt, split));
	new = get_new_obj(CIRCLE);
	if (!new)
		return (print_error("Circle object allocation fail", line_cnt, split));
	ft_lstadd_back(&scene->list, new);
	if (get_vector(&((t_object *)new->content)->pos, split[1],
			COORDINATES, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_vector(&((t_object *)new->content)->cl.orient, split[2],
			ORIENTATION, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	((t_object *)new->content)->cl.dia = ft_atod(split[3], &error);
	if (error == ERROR)
		return (print_error("Circle diameter can't be converted",
				line_cnt, split));
	if (get_colors(&((t_object *)new->content)->colors, split[4],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	ft_free_array(split);
	return (0);
}

static int	get_cy_circle_2(t_list *new, char **split, int line_cnt)
{
	int		error;

	error = 0;
	if (get_vector(&((t_object *)new->content)->cl.orient, split[2],
			ORIENTATION, line_cnt) == ERROR)
		return (ERROR);
	((t_object *)new->content)->cl.dia = ft_atod(split[3], &error);
	if (error == ERROR)
		return (print_error("Circle diameter can't be converted",
				line_cnt, NULL));
	if (get_colors(&((t_object *)new->content)->colors, split[5],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	return (0);
}

int	get_cy_circle(t_scene *scene, char **split, int line_cnt, t_vec3d pos)
{
	t_list	*new;

	if (arrlen(split) != 6)
		return (print_error("Wrong circle input", line_cnt, split));
	new = get_new_obj(CIRCLE);
	if (!new)
		return (print_error("Cylinder circle object can't be allocated",
				line_cnt, NULL));
	ft_lstadd_back(&scene->list, new);
	if (check_range(-500.0, 500.0, pos.x) == false
		|| check_range(-500.0, 500.0, pos.y) == false
		|| check_range(-500.0, 500.0, pos.z) == false)
		return (print_error("Coordinate vector is not in range [-500.0,500.0]",
				line_cnt, NULL));
	((t_object *)new->content)->pos = pos;
	if (get_cy_circle_2(new, split, line_cnt) == ERROR)
		return (ERROR);
	return (0);
}
