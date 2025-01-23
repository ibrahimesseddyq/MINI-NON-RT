/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:38:19 by sessarhi          #+#    #+#             */
/*   Updated: 2025/01/23 20:19:56 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../../minirt.h"

void int_tsceen(t_tscene *tscene)
{
    tscene->cylinder = NULL;
    tscene->plane = NULL;
    tscene->sphere = NULL;
    tscene->plane_size = 0;
    tscene->cylinder_size = 0;
    tscene->sphere_size = 0;
    tscene->is_c_set = false;
    tscene->is_a_set = false;
    tscene->camera.position.x = 0;
    tscene->camera.position.y = 0;
    tscene->camera.position.z = 0;
    tscene->camera.direction.x = 0;
    tscene->camera.direction.y = 0;
    tscene->camera.direction.z = 0;
}

bool mange_line(char *buffer, int *ret, int *backup)
{
    int i = *ret;
    buffer[i--] = '\0';
    while(i > 0 && buffer[i] != '\n')
        i--;
    if (i == 0 && buffer[i] != '\n')
        return false;
    *backup = *ret - i;
    buffer[i] = '\0';
    *ret = i;
    return true;
}
void restor_line(char **buffer, int *ret, int *backup)
{
    int i = 0;
    char *buf = *buffer; 
    *ret += 1;
    while(buf[*ret] != '\0')
    {
        buf[i] = buf[*ret];
        i++;
        (*ret)++;
    }
    *backup = i;
}
void   process_flie(char **av , t_scene *scene)
{
    int fd;
    ssize_t ret;
    char *buffer;
    t_tscene tscene;
    int backup;
    
    int_tsceen(&tscene);
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return (printf("Error can't open %s\n",*av),exit(1));
    buffer = malloc(BUFFER_SIZE);
    ret = read(fd, buffer, BUFFER_SIZE);
    while (ret > 0)
    {
        if (!mange_line(buffer, &ret, &backup))
            return (printf("error file empty or line too long\n"),exit(1));
        buffer[ret] = '\0';
        splil_line(buffer, &tscene);
        restor_line(&buffer, &ret, &backup);
        ret = read(fd, buffer + backup, BUFFER_SIZE - backup);
        if (ret == 0 )
        {
            buffer[backup + ret] = '\0';
            splil_line(buffer, &tscene);
        }
    }
    free(buffer);
    copy_tscene(&tscene, scene);
    close(fd);
}
