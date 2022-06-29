/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:28:43 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 12:02:58 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_plane(t_scene *scene, char **split, int line_cnt)
{
	t_list	*new_elem;

	if (arrlen(split) != 5)
		return (print_error("Wrong plane input", line_cnt, split));
	new_elem = get_new_obj(PLANE);
	if (!new_elem)
		return (print_error("Plane obj can't be allocated", line_cnt, split));
	ft_lstadd_back(&scene->list, new_elem);
	if (get_vector(&((t_object *)new_elem->content)->pos, split[1],
			COORDINATES, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_vector(&((t_object *)new_elem->content)->pl.orient, split[2],
			ORIENTATION, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_colors(&((t_object *)new_elem->content)->colors, split[3],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_material((t_object *)new_elem->content, split[4],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	ft_free_array(split);
	return (0);
}

int	get_sphere(t_scene *scene, char **split, int line_cnt)
{
	t_list	*new;
	double	dia;
	int		error;

	error = 0;
	if (arrlen(split) != 5)
		return (print_error("Wrong sphere input", line_cnt, split));
	new = get_new_obj(SPHERE);
	if (!new)
		return (print_error("Sphere object can't be allocated",
				line_cnt, split));
	ft_lstadd_back(&scene->list, new);
	if (get_vector(&((t_object *)new->content)->pos, split[1],
			COORDINATES, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	dia = ft_atod(split[2], &error);
	if (error == ERROR)
		return (print_error("Sphere diameter can't be converted",
				line_cnt, split));
	((t_object *)new->content)->sp.diameter = dia;
	if (get_colors(&((t_object *)new->content)->colors, split[3],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_material((t_object *)new->content, split[4], line_cnt) == ERROR)
		return (error_free(ERROR, split));
	ft_free_array(split);
	return (0);
}

int	get_bowl(t_scene *scene, char **split, int line_cnt)
{
	t_list	*new;
	int		error;

	error = 0;
	if (arrlen(split) != 7)
		return (print_error("Wrong sphere input", line_cnt, split));
	new = get_new_obj(BOWL);
	if (!new)
		return (print_error("Bowl object can't be allocated", line_cnt, split));
	ft_lstadd_back(&scene->list, new);
	if (get_vector(&((t_object *)new->content)->pos, split[1],
			COORDINATES, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_vector(&((t_object *)new->content)->bo.orient, split[2],
			ORIENTATION, line_cnt) == ERROR)
		return (error_free(ERROR, split));
	((t_object *)new->content)->bo.angle = ft_atod(split[3], &error);
	if (error == ERROR)
		return (print_error("Bowl angle can't be converted", line_cnt, split));
	if (check_range(0.0, 180.0, ((t_object *)new->content)->bo.angle) == false)
		return (print_error("Bowl angle is not in range [0.0,180.0]",
				line_cnt, split));
	error = 0;
	((t_object *)new->content)->bo.diameter = ft_atod(split[4], &error);
	if (error == ERROR)
		return (print_error("Bowl diameter can't be converted",
				line_cnt, split));
	if (get_colors(&((t_object *)new->content)->colors, split[5],
			line_cnt) == ERROR)
		return (error_free(ERROR, split));
	if (get_material((t_object *)new->content, split[6], line_cnt) == ERROR)
		return (error_free(ERROR, split));
	ft_free_array(split);
	return (0);
}

int	get_obj(t_scene *scene, char **split, int line_cnt)
{
	if (split[0][0] == 'p' && split[0][1] == 'l')
		return (get_plane(scene, split, line_cnt));
	if (split[0][0] == 's' && split[0][1] == 'p')
		return (get_sphere(scene, split, line_cnt));
	if (split[0][0] == 'b' && split[0][1] == 'o')
		return (get_bowl(scene, split, line_cnt));
	if (split[0][0] == 'c' && split[0][1] == 'y')
	{
		if (get_cylinder(scene, split, line_cnt) == ERROR)
			return (error_free(ERROR, split));
		return (0);
	}
	if (split[0][0] == 't' && split[0][1] == 'b')
	{
		if (get_tube(scene, split, line_cnt) == ERROR)
			return (error_free(ERROR, split));
		return (0);
	}
	if (split[0][0] == 'c' && split[0][1] == 'l')
		return (get_circle(scene, split, line_cnt));
	else
		return (print_error("Object type doesn't exist", line_cnt, split));
}
