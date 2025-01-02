/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:09:07 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/02 16:14:27 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minirt.h"

int process_A(char **inf , t_tscene *tscene)
{
    if (!inf[1] || !inf[2] || inf[3])
        return (1);
    if (tscene->is_a_set == true)
        return (printf("Error multiple Ambient lights\n"),1);
    tscene->ambient.ratio = ft_atof(inf[1]);
    if (!parse_rgb(inf[2],&tscene->ambient.color)
    || tscene->ambient.ratio < 0 || tscene->ambient.ratio > 1)
        return (1);
    tscene->is_a_set = true;
    return (0);
}

int process_C(char **inf , t_tscene *t_scene)
{
    if (!inf[1] || !inf[2] || !inf[3] || inf[4])
        return (1);
    if (t_scene->is_c_set == true)
        return (printf("Error multiple Cameras\n"),1);
    t_scene->camera.fov = atoi(inf[3]);
    if (!parse_crd(inf[1],&t_scene->camera.position) 
    || !parse_crd(inf[2], &t_scene->camera.direction))
        return (1);
    t_vector normalized_dir = vector_normalize(&t_scene->camera.direction);
    t_scene->camera.direction.x = normalized_dir.x;
    t_scene->camera.direction.y = normalized_dir.y;
    t_scene->camera.direction.z = normalized_dir.z;
    if (t_scene->camera.fov > 180 || t_scene->camera.fov < 0 || t_scene->camera.direction.x < -1 ||
    t_scene->camera.direction.x > 1 || t_scene->camera.direction.y < -1 || t_scene->camera.direction.y > 1 || 
    t_scene->camera.direction.z < -1 || t_scene->camera.direction.z > 1)
        return (1);
        
    t_scene->is_c_set = true;
    return (0);
}

int process_L(char **inf , t_tscene *t_scene)
{
    if (!inf[1] || !inf[2] || !inf[3] || inf[4])
        return (1);
    if (t_scene->is_l_set == true)
        return (printf("Error multiple Lights\n"),1);
    t_scene->light.bratio = ft_atof(inf[2]);
    if (!parse_crd(inf[1], &t_scene->light.position) ||
     !parse_rgb(inf[3], &t_scene->light.color) ||
      t_scene->light.bratio < 0 || t_scene->light.bratio > 1)
        return (1);

    t_scene->is_l_set = true;
    return (0);
}

int process_sp(char **inf ,t_tscene *t_scene)
{
    t_tsphere *new;

    new = new_sphere();
    if (!inf[1] || !inf[2] || !inf[3] || inf[4])
        return (1);
    new->diameter = ft_atof(inf[2]);
    if (!parse_crd(inf[1],&new->position) ||
        !parse_rgb(inf[3], &new->color) ||
         new->diameter == (float)INT_MIN)
            return (1);
    sphere_add_front(&t_scene->sphere, new);
    t_scene->sphere_size++;
    return (0);
}

int process_pl(char **inf , t_tscene *t_scene)
{
    t_tplane *new;

    new = new_plane();
    if (!inf[1] || !inf[2] || !inf[3] || inf[4])
        return (1);
    if (!parse_crd(inf[1], &new->position) ||
     !parse_crd(inf[2], &new->direction) ||
     !parse_rgb(inf[3], &new->color))
        return (1);
    plane_add_front(&t_scene->plane, new);
    t_scene->plane_size++;
    return (0);
}

int process_cy(char **inf , t_tscene *t_scene)
{
    t_tcylinder *new;

    new = new_cylinder();
    if (!inf[1] || !inf[2] || !inf[3] || !inf[4] || !inf[5] || inf[6])
        return (1);
    new->diameter = ft_atof(inf[3]);
    new->height = ft_atof(inf[4]);
    if  (!parse_crd(inf[1], &new->position) ||
     !parse_crd(inf[2], &new->direction) ||
     !parse_rgb(inf[5], &new->color) ||
      new->diameter == (float)INT_MIN || new->height == (float)INT_MIN)
        return (1);
    cylinder_add_front(&t_scene->cylinder, new);
    t_scene->cylinder_size++;
    return (0);
}
void splil_line(const char *line , t_tscene *tscene)
{
    char **elm;
    char **inf;
    int i = 0;
    
    elm = ft_split(line, '\n');
    while (elm[i])
    {
        // printf("%s\n", elm[i]);
        inf = ft_split(elm[i], ' ');
        if (strcmp(inf[0] ,"A") == 0 && !process_A(inf , tscene))
                i++;
        else if (strcmp(inf[0], "C") == 0 && !process_C(inf  ,tscene))
                i++;
        else if (strcmp(inf[0], "L") == 0 && !process_L(inf ,tscene))
                i++;
        else if (strcmp(inf[0], "sp") == 0 && !process_sp(inf ,tscene))
                i++;
        else if (strcmp(inf[0], "pl") == 0 && !process_pl(inf ,tscene))
            i++;
        else if (strcmp(inf[0], "cy") == 0 && !process_cy(inf ,tscene))
            i++;
        else 
            return (printf("Error \n"),exit(1));
    }
    printf("OK\n");
}

void int_tsceen(t_tscene *tscene)
{
    tscene->cylinder = NULL;
    tscene->plane = NULL;
    tscene->sphere = NULL;
    tscene->plane_size = 0;
    tscene->cylinder_size = 0;
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
void print_data(t_scene *scene)
{
    int i = 0;
    while (scene->plane_count--)
    {
        printf("Plane id %d\n", scene->plane[i].id);
        i++;
    }
    i = 0;
    while (scene->sphere_count--)
    {
        printf("Sphere id %d\n", scene->sphere[i].id);
        i++;
    }
    i = 0;
    while (scene->cylinder_count--)
    {
        printf("Cylinder id %d\n", scene->cylinder[i].id);
        i++;
    }
    
}

void copy_tscene(t_tscene *tscene, t_scene *scene)
{
    scene->ambient = tscene->ambient;

    scene->camera = tscene->camera;
    scene->light = tscene->light;
    scene->cylinder = arena_alloc(*get_arena(), sizeof(t_cylinder) * tscene->cylinder_size);
    scene->plane = arena_alloc(*get_arena(), sizeof(t_plane) * tscene->plane_size);
    scene->sphere = arena_alloc(*get_arena(), sizeof(t_sphere) * tscene->sphere_size);
    scene->cylinder_count = tscene->cylinder_size;
    scene->plane_count = tscene->plane_size;
    scene->sphere_count = tscene->sphere_size;
    scene->viewport_dist = 1.0;
    int id = 0;
    t_tsphere *sphere;
    t_tplane *plane;
    t_tcylinder *cylinder;
    int i = 0;
    while (tscene->plane)
    {
        scene->plane[i].position = tscene->plane->position;
        scene->plane[i].direction = tscene->plane->direction;
        scene->plane[i].color = tscene->plane->color;
        scene->plane[i].id = id++;
        tscene->plane = tscene->plane->next;
        i++;
    }
    i = 0;
    while (tscene->sphere)
    {
        scene->sphere[i].position = tscene->sphere->position;
        scene->sphere[i].diameter = tscene->sphere->diameter;
        scene->sphere[i].color = tscene->sphere->color;
        scene->sphere[i].id = id++;
        tscene->sphere = tscene->sphere->next;
        i++;
    }

    i = 0;
    while (tscene->cylinder)
    {
        scene->cylinder[i].position = tscene->cylinder->position;
        scene->cylinder[i].direction = tscene->cylinder->direction;
        scene->cylinder[i].diameter = tscene->cylinder->diameter;
        scene->cylinder[i].height = tscene->cylinder->height;
        scene->cylinder[i].color = tscene->cylinder->color;
        scene->cylinder[i].id = id++;
        tscene->cylinder = tscene->cylinder->next;
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
    (void)scene;
    close(fd);
}
