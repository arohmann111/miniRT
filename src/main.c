

#include "miniRT.h"

void	init_struct(t_scene *scene)
{
	scene->ambiente.is_set = false;
	scene->camera.is_set = false;
	scene->light.is_set = false;
	scene->res.is_set = false;
	scene->bg.is_set = false;
	scene->list = NULL;
	scene->mlx = NULL;
	scene->hit = HIT;
	scene->bg.col = (t_colors){200.0,230.0,250.0};
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







// /* random scene generator */
// void	create_scene(int fd)
// {
// 	dprintf(fd, "#ambient light\n##A ratio,            colors\nA   0.0               255,255,255\n\n");
// 	dprintf(fd, "#camera\n##C pos,              dir,               fov\nC   -110,50,160          0.7,-0.5,-1           60\n\n");
// 	dprintf(fd, "#light\n##L  pos,             brightness ratio,  colors\nL    0,10,30          0.0                255,255,255\n\n");
// 	dprintf(fd, "#resolution\n##R  width            height\nR    800              800\n\n");
// 	dprintf(fd, "#background\n##B  colors\nB    200,200,200\n\n");
// 	dprintf(fd, "#plane\n##pl pos              dir                colors\npl   0,0,0            0,1.0,0            100,150,170\n\n");

// 	dprintf(fd, "#sphere\n##sp pos,                           diameter,          colors\n");
// 	int z = -100;
// 	double dia = ft_rand_double(5, 15);
// 	while (z < 151)
// 	{
// 		int i = -80;
// 		while(i < 61)
// 		{
// 			dprintf(fd, "sp   %.2f,%.2f,%.2f            %.2f               %.0f,%.0f,%.0f\n", (double)i, dia / 2, (double)z, dia, ft_rand_double(0, 255), ft_rand_double(0, 255), ft_rand_double(0, 255));
// 			dia = ft_rand_double(5, 15);
// 			i = i + 20;
// 		}
// 		z = z + 50;
// 	}
// }

// void	random_scene()
// {
// 	int fd;

// 	fd = open("random_scene.rt", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	create_scene(fd);
// 	close(fd);
// }

// int	main()
// {
// 	t_scene	scene;

// 	srand(time(0));
// 	init_struct(&scene);
// 	random_scene();
// 	if (read_file(&scene, "random_scene.rt") == ERROR)
// 	{
// 		ft_lstclear(&scene.list, free);
// 		return (ERROR);
// 	}
// 	mlx_stuff(&scene);
// 	return (0);
// }