#include "./../../../minirt_bonus.h"

void cone_add_front(t_tcone **head, t_tcone *new)
{
  if (!*head)
  {
    *head = new;
    return;
  }
    new->next = *head;
    *head = new;
}

t_tcone* new_cone()
{
    t_tcone *cone;
    
    cone = malloc(sizeof(t_tcone));
    cone->vertex.x = 0;
    cone->vertex.y = 0;
    cone->vertex.z = 0;
    cone->axis.x = 0;
    cone->axis.y = 0;
    cone->axis.z = 0;
    cone->angle = 0;
    cone->height = 0;
    cone->color.r = 0;
    cone->color.g = 0;
    cone->color.b = 0;
    cone->next = NULL;
    return (cone);
}