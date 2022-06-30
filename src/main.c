/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:23:07 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/30 14:22:37 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_struct(t_scene *scene)
{
	scene->ambiente.is_set = false;
	scene->camera.is_set = false;
	scene->res.is_set = false;
	scene->bg.is_set = false;
	scene->list = NULL;
	scene->lights = NULL;
	scene->mlx = NULL;
	scene->hit = HIT;
	scene->light_c = (t_colors){0.0, 0.0, 0.0};
	scene->bg.col = (t_colors){0.0, 0.0, 0.0};
}

int	main(int ac, char **av)
{
	t_scene	scene;
	int		fd;

	srand(time(0));
	init_struct(&scene);
	if (ac != 2)
		return (print_input_instructions());
	if (ft_strrncmp(av[1], ".rt", 3) != 0)
	{
		ft_putendl_fd("Error\nFile must be an .rt file", STDERR_FILENO);
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == ERROR || read_file(&scene, fd) == ERROR)
	{
		ft_lstclear(&scene.list, free);
		return (ERROR);
	}
	mlx_stuff(&scene);
	return (0);
}
