#ifndef MINIRT_H
# define MINIRT_H

/* includes */
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

/* macros */

# define ERROR -1
# define SUCCESS 0

/* enums */
enum e_object
{
	PLANE,
	LIGHT,
	CAMERA,
	A_LIGHT,
	SPHERE,
	CYLINNDER
};

/* structs */
typedef struct s_vec3d
{
	int	x;
	int	y;
	int	z;
}t_vec3d;

typedef struct s_vec2d
{
	int	x;
	int	y;
}t_vec2d;

typedef struct s_sphere
{
	t_vec3d coord;
	char hannes;
}t_sphere;

typedef struct s_cylinder
{
	t_vec3d coord;
	t_vec3d orient;
	double	diameter;
	double	hight;
	char hannes;
}t_cylinder;

typedef struct s_object
{
	void *data;
	enum e_object type;
	struct s_object *next;
}t_object;

typedef struct s_scene
{
	int hight;
	int width;
	t_object object;
}t_scene;

/* prototypes */
int	read_file(char *file);



#endif