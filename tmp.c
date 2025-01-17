    if (intersection.hit)
    {
        t_vector scl = vector_scale(&ray->direction, t);
        intersection.point = vector_add(&ray->origin, &scl);
        t_vector cp = vector_sub(&intersection.point, &scene->cylinder[0].position);
        FLOAT proj_len = vector_dot(&cp, &scene->cylinder[0].direction);
        t_vector proj = vector_scale(&scene->cylinder[0].direction, proj_len);
        intersection.normal = vector_sub(&cp, &proj);
        intersection.normal = vector_normalize(&intersection.normal);
        float ambient_r = (scene->ambient.color.r) * scene->ambient.ratio;
        float ambient_g = (scene->ambient.color.g) * scene->ambient.ratio;
        float ambient_b = (scene->ambient.color.b) * scene->ambient.ratio;
        t_vector light_dir = vector_sub(&intersection.point, &scene->light.position);
        light_dir = vector_normalize(&light_dir);
        FLOAT diff = fmax(0.0, vector_dot(&intersection.normal, &light_dir));
        float diffuse_r = (scene->light.color.r) * scene->light.bratio * diff;
        float diffuse_g = (scene->light.color.g) * scene->light.bratio * diff;
        float diffuse_b = (scene->light.color.b) * scene->light.bratio * diff;
        FLOAT red = (ambient_r + diffuse_r) * scene->cylinder->color.r;
        FLOAT green = (ambient_g + diffuse_g) * scene->cylinder->color.g;
        FLOAT blue = (ambient_b + diffuse_b) * scene->cylinder->color.b;
        t_color final_color = {red, green, blue};
        return (colorToRgb(&final_color));
    }