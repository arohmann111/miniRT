

#include "miniRT.h"

void	init_struct(t_scene *scene)
{
	scene->ambiente.is_set = false;
	scene->camera.is_set = false;
	scene->light.is_set = false;
	scene->res.is_set = false;
	scene->list = NULL;
	scene->mlx = NULL;
	scene->hit = HIT;
	scene->bg.col = (t_colors){200,230,250};
}

int	print_input_instructions(void)
{
	ft_putendl_fd("Wrong number of arguments", STDERR_FILENO);
	ft_putendl_fd("Try: ./miniRT <file.rt>", STDERR_FILENO);
	return (ERROR);
}

int	main(int ac, char **av)
{
	t_scene	scene;

	srand(time(0));
	init_struct(&scene);
	// printf("%d\n", scene.res.is_set);
	if (ac != 2)
		return (print_input_instructions());
	if (read_file(&scene, av[1]) == ERROR)
	{
		ft_lstclear(&scene.list, free);
		return (ERROR);
	}
	mlx_stuff(&scene);
	return (0);
}
