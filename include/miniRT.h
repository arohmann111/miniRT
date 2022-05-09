#ifndef MINIRT_H
# define MINIRT_H

/* includes */
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

/* macros */

# define ERROR -1
# define SUCCESS 0
# define NEXT_NUM 1
# define NEXT_SPACE 2
# define ORIENTATION 0
# define COORDINATES 1
# define 

/* enums */
enum e_object
{
	NONE,
	PLANE,
	SPHERE,
	CYLINDER
};

/* structs */
typedef struct s_vec3d
{
	double	x;
	double	y;
	double	z;
}t_vec3d;

typedef struct s_colors
{
	int	r;
	int	g;
	int	b;
}t_colors;

// typedef struct s_vec2d
// {
// 	int	x;
// 	int	y;
// }t_vec2d;

typedef struct s_sphere
{
	double		diameter;
}t_sphere;

typedef struct s_plane
{
	t_vec3d		orient;
}t_plane;

typedef struct s_cylinder
{
	t_vec3d		orient;
	double		diameter;
	double		height;
}t_cylinder;

typedef struct s_object
{
	enum e_object	type;
	t_vec3d			pos;
	t_colors		colors;
	union
	{
		t_cylinder	cy;
		t_sphere	sp;
		t_plane		pl;
	};
	
}t_object;

typedef struct s_ambiente
{
	bool		is_set;
	double		ratio;
	t_colors	colors;
}t_ambiente;

typedef struct s_camera
{
	bool		is_set;
	t_vec3d		pos;
	t_vec3d		orient;
	int		fov;
}t_camera;

typedef struct s_light
{
	bool		is_set;
	t_vec3d		pos;
	double		bright;
	t_colors	colors;
}t_light;

typedef struct s_res
{
	bool		is_set;
	int			width;
	int			height;
}t_res;

typedef struct s_scene
{
	t_ambiente	ambiente;
	t_light		light;
	t_camera	camera;
	t_res		res;
	t_list		*list;
}t_scene;

/* prototypes */
int	read_file(t_scene * scene, char *file);
int	print_error(char *err_msg, int line_cnt);



#endif