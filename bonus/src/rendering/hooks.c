#include "./../../../minirt_bonus.h"

int	key_hook(int keycode, t_scene *scene)
{
	return (0);
}

int	hook(t_scene *scene)
{
	mlx_destroy_window(scene->mlx, scene->win);
	exit(0);
	return (0);
}
