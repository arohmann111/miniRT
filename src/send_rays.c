


// k = height / width (um Wert in range [0,1] zu bekommen) -> Verschiebung auf y-Achse


//cross(camdir, y-achse) = vec-w
//cross(w, camdir) = vec-q
//w normieren
//len(w) = tan(fov / 2) -> wenn w normiert
// q normieren
//len(q) = k * len(w)

//pt = pos + dir - w - q -> linke untere Ecke vom Bild
//a = w / (0.5*width) -> bei width = Anzahl Pixel in Breite
//b = q / (0.5*height) -> bei height = Anzahl Pixel in Bildschirmhöhe

//pt = Koordinaten (0/0) von origin aus -> campos abziehen um von pos auszugehen
//vector für pixel = (pt-campos) + x*a + y*b -> pt-campos = Koordinaten (0/0) von cam aus
// vector für pixel normieren



#include "miniRT.h"

t_vec3d	mk_v(double x, double y, double z)
{
	t_vec3d	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}



/* w: vec from middle to right edge */
/* q: vec from middle to upper edge */
/* p: vec from origin to left bottom corner // Eckpunkt */
/* px: vec from p in dir x-axis with length of one pixel */
/* py: vec from p in dir y-axis with length of one pixel */
t_vec3d	get_corner_pixel(t_scene *scene)
{
	double	relation;
	t_vec3d	w;
	t_vec3d	q;
	t_vec3d	p;

	relation = (double)scene->res.height / (double)scene->res.width;
	w = cross_vec3d(scene->camera.orient, mk_v(0.0, 1.0, 0.0));
	q = cross_vec3d(w, scene->camera.orient);

	w = norm_vec3d(w);
	w = multi_vec3d(w, tan((scene->camera.fov / 2.0) / 180 * M_PI));
	q = norm_vec3d(q);
	q = multi_vec3d(q, relation * tan((scene->camera.fov / 2.0) / 180 * M_PI));

printf("tan: %f fov: %d\n", tan((scene->camera.fov / 2.0) / 180 * M_PI), scene->camera.fov);
	printf("w: %f %f %f \nq: %f %f %f\n", w.x, w.y, w.z, q.x, q.y, q.z);

	p = sub_vec3d(add_vec3d(scene->camera.pos, scene->camera.orient), add_vec3d(w, q));
	scene->px = div_vec3d(w, (0.5 * scene->res.width));
	scene->py = div_vec3d(q, (0.5 * scene->res.height));
//loop?

	return (sub_vec3d(p, scene->camera.pos));
}
