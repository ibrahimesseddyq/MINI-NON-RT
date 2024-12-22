#ifndef MAP_H
#define MAP_H
#include "math.h"
#include "./../MLX/mlx.h"
typedef struct s_map
{
    t_color **points;
} t_map;

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_img;

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    t_img   img;
} t_mlx;

typedef struct s_data
{
    t_mlx   *mlx;
    t_scene *scene;
    t_map   *map;
} t_data;
void render(t_scene *scene);

#endif