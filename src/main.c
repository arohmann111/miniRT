/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:57:53 by arohmann          #+#    #+#             */
/*   Updated: 2022/05/06 16:09:06 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_struct(t_scene *scene)
{
	scene->ambiente.is_set = false;
	scene->camera.is_set = false;
	scene->light.is_set = false;
}

int	main(int ac, char **av)
{
	t_scene	scene;

	init_struct(&scene);
	if (ac != 2)
		return (print_error("wrong number of arguments\nTry: ./miniRT <file.rt>\n"));
	if (read_file(&scene, av[1]) == ERROR)
		return (print_error("File cannot be read\n"));
	return (0);
}
