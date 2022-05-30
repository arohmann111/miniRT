#ifndef MINIRT_H
# define MINIRT_H

/* ************************************************************************** */
/*                                  includes                                  */
/* ************************************************************************** */
# include "libft.h"
# include "MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <time.h>
# include <stdbool.h>


/* ************************************************************************** */
/*                                   macros                                   */
/* ************************************************************************** */
# define ERROR -1
# define SUCCESS 0
# define NEXT_NUM 1
# define NEXT_SPACE 2
# define ORIENTATION 0
# define COORDINATES 1
# define SAMPLE 20
# define BOUNCES 50
# define HIT 10000.0



/* ************************************************************************** */
/*                                    enums                                   */
/* ************************************************************************** */
enum e_object
{
	NONE,
	PLANE,
	SPHERE,
	TUBE,
	CIRCLE,
	CYLINDER
};

/* ************************************************************************** */
/*                                   structs                                  */
/* ************************************************************************** */
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

typedef struct s_sphere
{
	double		diameter;
}t_sphere;

typedef struct s_plane
{
	t_vec3d		orient;
}t_plane;

typedef struct s_tube
{
	t_vec3d		orient;
	double		diameter;
	double		height;
}t_tube;

typedef struct s_circle
{
	double		dia;
	t_vec3d		orient;
}t_circle;

// typedef struct s_cylinder
// {
// 	t_tube		body;
// 	t_vec3d		t_pos;
// 	t_vec3d		b_pos;
// 	t_circle	top;
// 	t_circle	bottom;
// }t_cylinder;

typedef struct s_object
{
	enum e_object	type;
	t_vec3d			pos;
	t_colors		colors;
	union
	{
		t_tube		tb;
		t_circle	cl;
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
	int			fov;
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

typedef struct s_bg
{
	bool		is_set;
	t_colors	col;
}t_bg;

typedef struct s_ray
{
	t_vec3d		pos;
	t_vec3d		dir;
	t_colors	col;
}t_ray;

typedef struct s_scene
{
	double		hit;
	t_vec3d		px;
	t_vec3d		py;
	t_ambiente	ambiente;
	t_light		light;
	t_camera	camera;
	t_res		res;
	t_bg		bg;
	t_list		*list;
	mlx_t		*mlx;
}t_scene;

/* ************************************************************************** */
/*                                  prototypes                                */
/* ************************************************************************** */
/* parsing */
int	read_file(t_scene * scene, char *file);


/* window */
int32_t		mlx_stuff(t_scene *scene);
t_vec3d		get_corner_pixel(t_scene *scene);
t_colors	trace(t_scene *scene, t_ray ray, int bounces);
int			col(int r, int g, int b);
int			multisample(t_scene	*scene, t_vec3d pix, int x, int y);
t_colors	mk_c(int r, int g, int b);

int	old_trace(t_scene *scene, t_vec3d dir);

double	ft_rand_double(double min, double max);

/* error handling */
int	print_error(char *err_msg, int line_cnt);

/* math functions */
t_vec3d	add_vec3d(t_vec3d one, t_vec3d two);
t_vec3d	sub_vec3d(t_vec3d one, t_vec3d two);
t_vec3d	multi_vec3d(t_vec3d vec, double t);
double	skalar_vec3d(t_vec3d one, t_vec3d two);
double	len_vec3d(t_vec3d vec);
t_vec3d	div_vec3d(t_vec3d vec, double t);
t_vec3d	norm_vec3d(t_vec3d vec);
t_vec3d	cross_vec3d(t_vec3d one, t_vec3d two);
t_vec3d	mk_v(double x, double y, double z);


#endif