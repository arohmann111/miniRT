/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:18:59 by arohmann          #+#    #+#             */
/*   Updated: 2022/06/30 14:23:17 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define ORIENTATION 0
# define COORDINATES 1
# define SAMPLE 20
# define HIT 1000.0

/* ************************************************************************** */
/*                                    enums                                   */
/* ************************************************************************** */
enum e_object
{
	NONE,
	PLANE,
	SPHERE,
	BOWL,
	TUBE,
	CIRCLE
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

typedef struct s_bowl
{
	t_vec3d		orient;
	double		diameter;
	double		angle;
}t_bowl;

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
		t_bowl		bo;
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
	t_colors	light_c;
	t_vec3d		px;
	t_vec3d		py;
	t_ambiente	ambiente;
	t_list		*lights;
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
int			read_file(t_scene *scene, int fd);
int			get_ambiente(t_scene *scene, char **split, int line_cnt);
int			get_camera(t_scene *scene, char **split, int line_cnt);
int			get_resolution(t_scene *scene, char **split, int line_cnt);
int			get_background(t_scene *scene, char **split, int line_cnt);
int			get_light(t_scene *scene, char **split, int line_cnt);
int			get_tube(t_scene *scene, char **split, int line_cnt);
int			get_circle(t_scene *scene, char **split, int line_cnt);
int			get_cy_circle(t_scene *scene, char **split,
				int line_cnt, t_vec3d pos);
int			get_cylinder(t_scene *scene, char **split, int line_cnt);
int			get_sphere(t_scene *scene, char **split, int line_cnt);
int			get_plane(t_scene *scene, char **split, int line_cnt);
int			get_bowl(t_scene *scene, char **split, int line_cnt);

/* utils */
int			arrlen(char **arr);
bool		check_range(double range_start, double range_end, double val);
int			check_must_haves(t_scene *scene);
int			get_vector(t_vec3d *v, char *split_str, int type, int line_cnt);
int			get_colors(t_colors *c, char *split_str, int line_cnt);
t_list		*get_new_l(void);
t_list		*get_new_obj(int type);

/* intersect */
double		find_t(t_object *obj, t_ray ray);
double		sp_find_t(t_object *sphere, t_ray ray);
double		bo_find_t(t_object *bowl, t_ray ray);
double		pl_find_t(t_object *plane, t_ray ray);
double		circ_find_t(t_object *circle, t_ray ray);
double		tube_find_t(t_object *tube, t_ray ray);
void		intersect_sphere(t_scene *scene, t_ray *ray, t_object *obj);
void		intersect_plane(t_scene *scene, t_ray *ray, t_object *obj);
void		intersect_tube(t_scene *scene, t_ray *ray, t_object *obj);
void		intersect_circle(t_scene *scene, t_ray *ray, t_object *obj);

/* light */
t_colors	get_multi_l(t_scene *scene, t_ray ray, t_vec3d n);
t_vec3d		in_unit_sphere(void);

/* colors */
int			col(int r, int g, int b);
t_colors	mk_c(int r, int g, int b);
t_colors	simple_multi_col(t_colors col, double factor);
t_colors	multi_colors(t_colors one, t_colors two);
t_colors	scale_color(t_colors c);
t_colors	add_col(t_colors col, t_colors color);

/* window */
void		mlx_stuff(t_scene *scene);
t_vec3d		get_corner_pixel(t_scene *scene);
t_colors	trace(t_scene *scene, t_ray ray);
int			multisample(t_scene	*scene, t_vec3d pix, int x, int y);
double		ft_rand_double(double min, double max);

/* error handling */
int			print_input_instructions(void);
int			print_error(char *err_msg, int line_cnt, char **arr);
int			error_free(int error, char **arr);

/* math functions */
t_vec3d		add_vec3d(t_vec3d one, t_vec3d two);
t_vec3d		sub_vec3d(t_vec3d one, t_vec3d two);
t_vec3d		multi_vec3d(t_vec3d vec, double t);
double		skalar_vec3d(t_vec3d one, t_vec3d two);
double		len_vec3d(t_vec3d vec);
t_vec3d		div_vec3d(t_vec3d vec, double t);
t_vec3d		norm_vec3d(t_vec3d vec);
t_vec3d		cross_vec3d(t_vec3d one, t_vec3d two);
t_vec3d		mk_v(double x, double y, double z);

#endif