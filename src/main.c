/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:23:07 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/29 11:45:59 by arohmann         ###   ########.fr       */
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

int	print_error(char *err_msg, int line_cnt, char **arr)
{
	ft_putstr_fd("Error in line ", STDERR_FILENO);
	ft_putnbr_fd(line_cnt, STDERR_FILENO);
	write(STDERR_FILENO, ":\n", 2);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (error_free(ERROR, arr));
}

int	error_free(int error, char **arr)
{
	if (arr != NULL)
	{
		ft_free_array(arr);
		arr = NULL;
	}
	return (error);
}

int	print_input_instructions(void)
{
	ft_putendl_fd("Error\nWrong number of arguments", STDERR_FILENO);
	ft_putendl_fd("Try: ./miniRT <file.rt>", STDERR_FILENO);
	return (ERROR);
}

int	main(int ac, char **av)
{
	t_scene	scene;

	srand(time(0));
	init_struct(&scene);
	if (ac != 2)
		return (print_input_instructions());
	if (ft_strrncmp(av[1], ".rt", 3) != 0)
	{
		ft_putendl_fd("Error\nFile must be an .rt file", STDERR_FILENO);
		return (1);
	}
	if (read_file(&scene, av[1]) == ERROR)
	{
		ft_lstclear(&scene.list, free);
		system("leaks miniRT");
		return (ERROR);
	}
	mlx_stuff(&scene);
	return (0);
}
