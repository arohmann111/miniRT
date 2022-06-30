/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:37:28 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/30 11:16:28 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	get_obj(t_scene *scene, char **split, int line_cnt)
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

static int	parsing(t_scene *scene, char *line, int line_cnt)
{
	char	**split;

	if (line[0] == '\n')
		return (0);
	split = ft_split(line, ' ');
	if (split == NULL)
		return (print_error("Split failed", line_cnt, NULL));
	else if (split[0][0] == 'A')
		return (get_ambiente(scene, split, line_cnt));
	else if (split[0][0] == 'C')
		return (get_camera(scene, split, line_cnt));
	else if (split[0][0] == 'L')
		return (get_light(scene, split, line_cnt));
	else if (split[0][0] == 'R')
		return (get_resolution(scene, split, line_cnt));
	else if (split[0][0] == 'B')
		return (get_background(scene, split, line_cnt));
	else
		return (get_obj(scene, split, line_cnt));
	return (0);
}

int	read_file(t_scene *scene, int fd)
{
	char	*line;
	int		line_cnt;

	line = NULL;
	line_cnt = 0;
	while (1)
	{
		if (line != NULL)
			free(line);
		line = get_next_line(fd);
		line_cnt++;
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (line[0] == '#' || line[0] == '\n' || line[0] == '\0')
			continue ;
		if (parsing(scene, line, line_cnt) != 0)
		{
			free(line);
			return (ERROR);
		}
	}
	free(line);
	return (check_must_haves(scene));
}
