#include "./../../includes/math.h"

FLOAT      deg_to_rad(FLOAT degrees)
{
    return (degrees * PI / 180.0);
}

FLOAT      rad_to_deg(FLOAT radians)
{
    return (radians * 180.0 / PI);
}
