/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:36:06 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 12:03:53 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	check_range(double range_start, double range_end, double val)
{
	if (!(val >= range_start && val <= range_end))
		return (false);
	return (true);
}

int	arrlen(char **arr)
{
	int	i;

	i = 1;
	if (!arr)
		return (-1);
	while (arr[i])
		i++;
	return (i);
}

t_list	*get_new_obj(int type)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object) * 1);
	if (!obj)
		return (NULL);
	obj->type = type;
	return (ft_lstnew(obj));
}

t_list	*get_new_l(void)
{
	t_light	*l;

	l = (t_light *)malloc(sizeof(t_light) * 1);
	if (!l)
		return (NULL);
	return (ft_lstnew(l));
}

int	check_must_haves(t_scene *scene)
{
	if (scene->ambiente.is_set == false || scene->camera.is_set == false
		|| scene->res.is_set == false)
	{
		ft_putendl_fd("Error: Mandatory scene file item is missing",
			STDERR_FILENO);
		return (ERROR);
	}
	return (0);
}
