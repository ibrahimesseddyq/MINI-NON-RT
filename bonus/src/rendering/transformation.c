#include "./../../../minirt_bonus.h"

int transformation(int keycode, t_scene *scene)
{
    static int keys[10] = {0};
    static int cursor = 0;
    int i;

    i = 0;
    if (cursor < 10) 
        keys[cursor++] = keycode;

    if (keycode == ALT_KEY)
    {
        for(int i = 0;i < 10; i++)
        {
            printf("key [%d]\n",keys[i]);
        }
        if (keys[0] == LEFT_ROW_KEY || keys[0] == UPPER_ROW_KEY ||
            keys[0] == RIGHT_ROW_KEY || keys[0] == DOWN_ROW_KEY)
            translate(keys, scene);
        else if (keys[0] == R_KEY)
            rotate(keys, scene);
        else if (keys[0] == S_KEY)
            resize(keys, scene);
        cursor = 0;
        while (i < 10)
        {
            keys[i] = 0;
            i++;
        }
    }

    if (keycode == ESC_KEY)
    {
        mlx_destroy_window(scene->mlx, scene->win);
        exit(0);
    }

    draw(scene);
    return (0);
}

void translate(int *keys, t_scene *scene)
{
    int obj_id;

    if ((char)keys[1] == 'c' || (char)keys[1] == 'l')
    {
        move_light_or_camera(keys, scene);
        return ;
    }
    obj_id = my_atoi(keys, 1);
    if (obj_id == -1) 
        return;
    for (int i = 0; i < scene->sphere_count; i++)
    {
        if (scene->sphere[i].id == obj_id)
        {
            move_sphere(keys, &scene->sphere[i]);
            return; 
        }
    }
    for (int i = 0; i < scene->cylinder_count; i++)
    {
        if (scene->cylinder[i].id == obj_id)
        {
            move_cylinder(keys, &scene->cylinder[i]);
            return; 
        }
    }
    for (int i = 0; i < scene->plane_count; i++)
    {
        if (scene->plane[i].id == obj_id)
        {
            move_plane(keys, &scene->plane[i]);
            return; 
        }
    }
}

void resize(int *keys, t_scene *scene)
{
    int obj_id = my_atoi(keys, 2);
    FLOAT ratio;

    if (keys[1] == KEY_PLUS)
        ratio = 1.1;
    else if (keys[1] == KEY_MINUS)
        ratio = 0.9;

    printf("obj_id: [%d]\n", obj_id);
    if (obj_id == -1) 
        return;
    for( int i = 0; i < scene->sphere_count; i++)
    {
        if (scene->sphere[i].id == obj_id)
        {
            scene->sphere[i].diameter *= ratio;
        }
    }
    for (int i = 0; i < scene->cylinder_count; i++)
    {
        if (scene->cylinder[i].id == obj_id)
        {
            scene->cylinder[i].height *= ratio;
            scene->cylinder[i].diameter *= ratio;
        }
    }
    for (int i = 0; i < scene->plane_count; i++)
    {
        if (scene->plane[i].id == obj_id)
        {
            scene->plane[i].direction.x *= ratio;
            scene->plane[i].direction.y *= ratio;
            scene->plane[i].direction.z *= ratio;

        }
    }
}

