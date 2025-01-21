/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:09:07 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/17 15:29:57 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./../../../minirt.h"
int process_co(char **inf , t_tscene *t_scene);

void splil_line(const char *line , t_tscene *tscene)
{
    char **elm;
    char **inf;
    int i = 0;
    
    elm = ft_split(line, '\n');
    printf("sefv3\n");

    while (elm[i])
    {
        inf = ft_split(elm[i], ' ');
    printf("sefv4\n");
        if (ft_strcmp(inf[0] ,"A") == 0 && !process_A(inf , tscene))
                i++;
        else if (ft_strcmp(inf[0], "C") == 0 && !process_C(inf  ,tscene))
                i++;
        else if (ft_strcmp(inf[0], "L") == 0 && !process_L(inf ,tscene))
                i++;
        else if (ft_strcmp(inf[0], "sp") == 0 && !process_sp(inf ,tscene))
                i++;
        else if (ft_strcmp(inf[0], "pl") == 0 && !process_pl(inf ,tscene))
            i++;
        else if (ft_strcmp(inf[0], "cy") == 0 && !process_cy(inf ,tscene))
            i++;
        else if (ft_strcmp(inf[0], "co") == 0 && !process_co(inf ,tscene))
            i++;
        else 
            return (printf("Error \n"),exit(1));
    }
    printf("sefv5\n");

    printf("cylinder position [%f]\n", tscene->cone->vertex.z);
    printf("OK\n");
}

void int_tsceen(t_tscene *tscene)
{
    tscene->cylinder = NULL;
    tscene->plane = NULL;
    tscene->sphere = NULL;
    tscene->plane_size = 0;
    tscene->cylinder_size = 0;
    tscene->cone_size = 0;

    tscene->sphere_size = 0;
    tscene->is_c_set = false;
    tscene->is_l_set = false;
    tscene->is_a_set = false;
    tscene->camera.position.x = 0;
    tscene->camera.position.y = 0;
    tscene->camera.position.z = 0;
    tscene->camera.direction.x = 0;
    tscene->camera.direction.y = 0;
    tscene->camera.direction.z = 0;
}
// void print_data(t_scene *scene)
// {
//     int i = 0;
//     while (scene->plane_count--)
//     {
//         printf("Plane id %d\n", scene->plane[i].id);
//         i++;
//     }
//     i = 0;
//     while (scene->sphere_count--)
//     {
//         printf("Sphere id %d\n", scene->sphere[i].id);
//         i++;
//     }
//     i = 0;
//     while (scene->cylinder_count--)
//     {
//         printf("Cylinder id %d\n", scene->cylinder[i].id);
//         i++;
//     }
    
// }

void copy_tscene(t_tscene *tscene, t_scene *scene)
{
    scene->ambient = tscene->ambient;
    scene->camera = tscene->camera;
    scene->light = tscene->light;
    scene->cylinder = arena_alloc(*get_arena(), sizeof(t_cylinder) * tscene->cylinder_size);
    scene->plane = arena_alloc(*get_arena(), sizeof(t_plane) * tscene->plane_size);
    scene->sphere = arena_alloc(*get_arena(), sizeof(t_sphere) * tscene->sphere_size);
    printf("cone size [%d]\n", tscene->cone_size);
    scene->cone = arena_alloc(*get_arena(), sizeof(t_cone) * tscene->cone_size);

    scene->cylinder_count = tscene->cylinder_size;
    scene->plane_count = tscene->plane_size;
    scene->sphere_count = tscene->sphere_size;
    scene->cone_count = tscene->cone_size;
    scene->viewport_dist = 1.0;
    int id = 0;
    int i = 0;
    while (tscene->plane)
    {
                printf("hi2\n");

        scene->plane[i].position = tscene->plane->position;
        scene->plane[i].direction = tscene->plane->direction;
        scene->plane[i].color = tscene->plane->color;
        scene->plane[i].texture_name = tscene->plane->texture_name;
        scene->plane[i].has_checkerboard = tscene->plane->has_checkerboard;
        scene->plane[i].id = id++;
        tscene->plane = tscene->plane->next;
        i++;
    }
    i = 0;
    while (tscene->sphere)
    {
                        printf("hi5\n");

        scene->sphere[i].position = tscene->sphere->position;
        scene->sphere[i].diameter = tscene->sphere->diameter;
        scene->sphere[i].color = tscene->sphere->color;
        scene->sphere[i].texture_name = tscene->sphere->texture_name;
        scene->sphere[i].has_checkerboard = tscene->sphere->has_checkerboard;

        scene->sphere[i].id = id++;
        tscene->sphere = tscene->sphere->next;
        i++;
    }

    i = 0;
    while (tscene->cylinder)
    {
        scene->cylinder[i].position = tscene->cylinder->position;
        scene->cylinder[i].direction = vector_normalize(&tscene->cylinder->direction);
        scene->cylinder[i].diameter = tscene->cylinder->diameter;
        scene->cylinder[i].height = tscene->cylinder->height;
        scene->cylinder[i].texture_name = tscene->cylinder->texture_name;
        scene->cylinder[i].color = tscene->cylinder->color;
        // scene->cylinder[i].has_checkerboard = tscene->cylinder->has_checkerboard;

        scene->cylinder[i].id = id++;
        tscene->cylinder = tscene->cylinder->next;
        i++;
    }

    i = 0;
    while (i < scene->cone_count )
    {
        printf("hi3\n");
        scene->cone[i].vertex = tscene->cone->vertex;
        scene->cone[i].axis = tscene->cone->axis;
        scene->cone[i].angle = tscene->cone->angle;
        scene->cone[i].texture_name = tscene->cone->texture_name;
        scene->cone[i].height = tscene->cone->height;
        scene->cone[i].color = tscene->cone->color;
        // scene->cone[i].has_checkerboard = tscene->cone->has_checkerboard;

        scene->cone[i].id = id++;
        tscene->cone = tscene->cone->next;
        i++;
    }
}

void   process_flie(char **av , t_scene *scene)
{
    int fd;
    ssize_t ret;
    char *buffer;
    t_tscene tscene;


    int_tsceen(&tscene);
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return (printf("Error can't open %s\n",*av),exit(1));
    buffer = malloc(BUFFER_SIZE);
    ret = read(fd, buffer, BUFFER_SIZE);
    while (ret > 0)
    {
        buffer[ret] = '\0';
        splil_line(buffer, &tscene);
        ret = read(fd, buffer, BUFFER_SIZE);
    }
    free(buffer);
    copy_tscene(&tscene, scene);
    close(fd);
}
