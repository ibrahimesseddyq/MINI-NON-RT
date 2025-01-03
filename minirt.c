/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:41:03 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/26 10:19:24 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int ac , char **av)
{
    t_scene scene;
    setup_arena();
    if (ac != 2)
        return (printf("Error bad arguments\n"));
    process_flie(av , &scene);
    render(&scene);
    return 0;
}