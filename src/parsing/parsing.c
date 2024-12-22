/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 21:09:07 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/22 19:43:14 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minirt.h"
#include "./../../includes/memory.h"

int process_A(char **inf , t_tscene *tscene)
{
    if (!inf[1] || !inf[2] || inf[3])
        return (1);
    if (tscene->is_a_set == true)
        return (printf("Error multiple Ambient lights\n"),1);
    tscene->ambient.ratio = ft_atof(inf[1]);
    if (!parse_rgb(inf[2], &tscene->ambient.r, &tscene->ambient.g, &tscene->ambient.b)
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
    if (!parse_crd(inf[1],&t_scene->camera.position.x, &t_scene->camera.position.y , &t_scene->camera.position.z) 
    || !parse_crd(inf[2], &t_scene->camera.direction.x, &t_scene->camera.direction.y, &t_scene->camera.direction.z)
    || t_scene->camera.fov > 180 || t_scene->camera.fov < 0 || t_scene->camera.direction.x < -1 ||
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
    if (!parse_crd(inf[1], &t_scene->light.position.x,&t_scene->light.position.y,&t_scene->light.position.z) ||
     !parse_rgb(inf[3], &t_scene->light.r, &t_scene->light.g, &t_scene->light.b) ||
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
    if (!parse_crd(inf[1], &new->x, &new->y, &new->z) ||
        !parse_rgb(inf[3], &new->r, &new->g, &new->b) ||
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
    if (!parse_crd(inf[1], &new->x, &new->y, &new->z) ||
     !parse_crd(inf[2], &new->vx, &new->vy, &new->vz) ||
     !parse_rgb(inf[3], &new->r, &new->g, &new->b))
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
    if  (!parse_crd(inf[1], &new->x, &new->y, &new->z) ||
     !parse_crd(inf[2], &new->vx, &new->vy, &new->vz) ||
     !parse_rgb(inf[5], &new->r, &new->g, &new->b) ||
      new->diameter == (float)INT_MIN || new->height == (float)INT_MIN)
        return (1);
    cylinder_add_front(&t_scene->cylinder, new);
    t_scene->cylinder_size++;
    return (0);
}
void splil_line(char line[] , t_tscene *tscene)
{
    char **elm;
    char **inf;
    int i = 0;
    
    elm = ft_split(line, '\n');
    while (elm[i])
    {
        printf("%s\n", elm[i]);
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
// void print_scene(t_tscene *tscene)
// {
//     t_tsphere *sphere;
//     t_tplane *plane;
//     t_tcylinder *cylinder;

//     sphere = tscene->sphere;
//     plane = tscene->plane;
//     cylinder = tscene->cylinder;
//     printf("Ambient\n");
//     printf("ratio : %f\n", tscene->ambient.ratio);
//     printf("r : %d\n", tscene->ambient.r);
//     printf("g : %d\n", tscene->ambient.g);
//     printf("b : %d\n", tscene->ambient.b);
//     printf("Camera\n");
//     printf("x : %f\n", tscene->camera.);
//     printf("y : %f\n", tscene->camera.y);
//     printf("z : %f\n", tscene->camera.z);
//     printf("vx : %f\n", tscene->camera.vx);
//     printf("vy : %f\n", tscene->camera.vy);
//     printf("vz : %f\n", tscene->camera.vz);
//     printf("fov : %d\n", tscene->camera.fov);
//     printf("Light\n");
//     printf("x : %f\n", tscene->light.x);
//     printf("y : %f\n", tscene->light.y);
//     printf("z : %f\n", tscene->light.z);
//     printf("bratio : %f\n", tscene->light.bratio);
//     printf("r : %d\n", tscene->light.r);
//     printf("g : %d\n", tscene->light.g);
//     printf("b : %d\n", tscene->light.b);
//     printf("Sphere size : %d\n", tscene->sphere_size);
//     printf("Plane size : %d\n", tscene->plane_size);
//     printf("Cylinder size : %d\n", tscene->cylinder_size);
//     printf("is_c_set : %d\n", tscene->is_c_set);
//     printf("is_l_set : %d\n", tscene->is_l_set);
//     printf("is_a_set : %d\n", tscene->is_a_set);
//     printf("Objects\n");
   
//     while (plane)
//     {
//          printf("Plane\n");
//         printf("x : %f\n", plane->x);
//         printf("y : %f\n", plane->y);
//         printf("z : %f\n", plane->z);
//         printf("vx : %f\n", plane->vx);
//         printf("vy : %f\n", plane->vy);
//         printf("vz : %f\n", plane->vz);
//         printf("r : %d\n", plane->r);
//         printf("g : %d\n", plane->g);
//         printf("b : %d\n", plane->b);
//         plane = plane->next;
//     }
//     while (sphere)
//     {
//          printf("Sphere\n");
//         printf("x : %f\n", sphere->x);
//         printf("y : %f\n", sphere->y);
//         printf("z : %f\n", sphere->z);
//         printf("diameter : %f\n", sphere->diameter);
//         printf("r : %d\n", sphere->r);
//         printf("g : %d\n", sphere->g);
//         printf("b : %d\n", sphere->b);
//         sphere = sphere->next;
//     }
    
//     while (cylinder)
//     {
//         printf("Cylinder\n");
//         printf("x : %f\n", cylinder->x);
//         printf("y : %f\n", cylinder->y);
//         printf("z : %f\n", cylinder->z);
//         printf("vx : %f\n", cylinder->vx);
//         printf("vy : %f\n", cylinder->vy);
//         printf("vz : %f\n", cylinder->vz);
//         printf("diameter : %f\n", cylinder->diameter);
//         printf("height : %f\n", cylinder->height);
//         printf("r : %d\n", cylinder->r);
//         printf("g : %d\n", cylinder->g);
//         printf("b : %d\n", cylinder->b);
//         cylinder = cylinder->next;
//     }
    
            

// }

void copy_tscene(t_tscene *tscene, t_scene *scene)
{
    scene->ambient = tscene->ambient;
        scene->width = 800;
            scene->height = 800;

    scene->camera = tscene->camera;
    scene->light = tscene->light;
    // printf("sphere size : %d\n", tscene->sphere_size);
    scene->cylinder = arena_alloc(*get_arena(), sizeof(t_cylinder) * tscene->cylinder_size);
    scene->plane = arena_alloc(*get_arena(), sizeof(t_plane) * tscene->plane_size);
    scene->sphere = arena_alloc(*get_arena(), sizeof(t_sphere) * tscene->sphere_size);
    scene->cylinder_count = tscene->cylinder_size;
    scene->plane_count = tscene->plane_size;
    scene->sphere_count = tscene->sphere_size;
    t_tsphere *sphere;
    t_tplane *plane;
    t_tcylinder *cylinder;
    int i = 0;
    sphere = tscene->sphere;
    plane = tscene->plane;
    cylinder = tscene->cylinder;
    while (plane)
    {
        scene->plane[i].position.x = plane->x;
        scene->plane[i].position.y = plane->y;
        scene->plane[i].position.z = plane->z;
        scene->plane[i].vx = plane->vx;
        scene->plane[i].vy = plane->vy;
        scene->plane[i].vz = plane->vz;
        scene->plane[i].r = plane->r;
        scene->plane[i].g = plane->g;
        scene->plane[i].b = plane->b;
        plane = plane->next;
        i++;
    }
    i = 0;
    while (sphere)
    {
        scene->sphere[i].position.x = sphere->x;
        scene->sphere[i].position.y = sphere->y;
        scene->sphere[i].position.z = sphere->z;
        scene->sphere[i].diameter = sphere->diameter;
        scene->sphere[i].r = sphere->r;
        scene->sphere[i].g = sphere->g;
        scene->sphere[i].b = sphere->b;
        sphere = sphere->next;
        i++;
    }
    i = 0;
    while (cylinder)
    {
        scene->cylinder[i].position.x = cylinder->x;
        scene->cylinder[i].position.y = cylinder->y;
        scene->cylinder[i].position.z = cylinder->z;
        scene->cylinder[i].vx = cylinder->vx;
        scene->cylinder[i].vy = cylinder->vy;
        scene->cylinder[i].vz = cylinder->vz;
        scene->cylinder[i].diameter = cylinder->diameter;
        scene->cylinder[i].height = cylinder->height;
        scene->cylinder[i].r = cylinder->r;
        scene->cylinder[i].g = cylinder->g;
        scene->cylinder[i].b = cylinder->b;
        cylinder = cylinder->next;
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
    // print_scene(&tscene);
    free(buffer);
    copy_tscene(&tscene, scene);
    (void)scene;
    close(fd);
}
