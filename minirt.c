/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibes-sed <ibes-sed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 13:41:03 by sessarhi          #+#    #+#             */
/*   Updated: 2024/12/19 23:17:16 by ibes-sed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "./includes/memory.h"

int main(int ac , char **av)
{
    t_scene scene;
    setup_arena();
    if (ac != 2)
        return (printf("Error bad arguments\n"));
    process_flie(av , &scene);
    return 0;
    
}