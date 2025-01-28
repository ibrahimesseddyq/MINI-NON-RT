
#include "./../../../minirt_bonus.h"
t_color	sample_texture(t_texture *texture, FLOAT u, FLOAT v);
t_vector	calculate_bump_normal(t_texture *bump_map, FLOAT u, FLOAT v,
					t_vector *original_normal);
t_color	get_checkerboard_color(t_color color1,
		t_color color2, FLOAT u, FLOAT v, FLOAT size);
void calculate_surface_properties(t_scene *scene, t_intersection *intersection, t_color *texture_color, t_vector *out_normal)
{
    t_vector normal = intersection->normal;
    t_color checker_board1 = {0,0,0};
    t_color checker_board2 = {255, 255, 255};
    int checker_size = 4;
    int set;

    set = 0;
    for (int i = 0; i < scene->plane_count; i++)
    {
        if (intersection->id == scene->plane[i].id)
        {
            if (scene->plane[i].has_checkerboard)
            {
                *texture_color = get_checkerboard_color(
                    checker_board1,
                    checker_board2,
                    intersection->u,
                    intersection->v,
                    checker_size
                );
                set = 1;
            }
            else if (scene->plane[i].texture_name)
            {
                *texture_color = sample_texture(&scene->plane[i].texture, intersection->u, intersection->v);
                normal = calculate_bump_normal(&scene->plane[i].texture,
                                                 intersection->u, intersection->v,
                                                 &intersection->normal);
                set = 1;
            }
        }
    }
    for (int i = 0; i < scene->sphere_count; i++)
    {
        if (intersection->id == scene->sphere[i].id)
        {
            if (scene->sphere[i].has_checkerboard)
            {
                *texture_color = get_checkerboard_color(
                    checker_board1,
                    checker_board2,
                    intersection->u,
                    intersection->v,
                    checker_size
                );
                set = 1;
            }
            else if (scene->sphere[i].texture_name)
            {
                *texture_color = sample_texture(&scene->sphere[i].texture, intersection->u, intersection->v);
                normal = calculate_bump_normal(&scene->sphere[i].texture,
                                                 intersection->u, intersection->v,
                                                 &intersection->normal);
                set = 1;
            }
        }
    }
    for (int i = 0; i < scene->cylinder_count; i++)
    {
        if (intersection->id == scene->cylinder[i].id)
        {
            if (scene->cylinder[i].has_checkerboard)
            {
                *texture_color = get_checkerboard_color(
                    checker_board1,
                    checker_board2,
                    intersection->u,
                    intersection->v,
                    checker_size
                );
                set = 1;
            }
            else if (scene->cylinder[i].texture_name)
            {
                *texture_color = sample_texture(&scene->cylinder[i].texture, intersection->u, intersection->v);
                normal = calculate_bump_normal(&scene->cylinder[i].texture,
                                                 intersection->u, intersection->v,
                                                 &intersection->normal);
                set = 1;
            }
        }
    }
    if (!set)
    {
        *texture_color = intersection->color;
    }
    *out_normal = normal;
}