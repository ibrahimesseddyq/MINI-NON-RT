/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:41:03 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/20 18:17:35 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "./includes/memory.h"

// void int_scene(t_scene *scene)
// {
//     scene->cylinder = NULL;
//     scene->plane = NULL;
//     scene->sphere = NULL;
//     scene->plane_count = 0;
//     scene->cylinder_count = 0;
//     scene->sphere_count = 0;
//     scene.
// }
int main(int ac , char **av)
{
    t_scene scene;
    setup_arena();
    if (ac != 2)
        return (printf("Error bad arguments\n"));
    process_flie(av , &scene);
    return 0;
    
}