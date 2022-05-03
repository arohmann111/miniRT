/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:58:19 by arohmann          #+#    #+#             */
/*   Updated: 2022/05/03 16:01:38 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define ERROR -1
# define SUCCESS 0

enum e_object
{
	PLANE,
	LIGHT,
	CAMERA,
	A_LIGHT,
	SPHERE,
	CYLINNDER
};

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
	s_vec3d coord;
	char hannes;
}t_sphere;

typedef struct s_cylinder
{
	s_vec3d coord;
	s_vec3d orient;
	double	diameter;
	double	hight;
	char hannes;
}t_cylinder;

typedef struct s_object
{
	void *data;
	enum e_object type;
	t_object *next;
}t_object;

typedef struct s_scene
{
	int hight;
	int width;
	t_object object;
}t_scene;

int	read_file(char *file);

#endif