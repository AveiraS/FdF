#include "fdf.h"
#include "utils.h"

double	percent(int start, int end, int current)
{
    double	placement;
    double	distance;

    placement = current - start;
    distance = end - start;
    return ((distance == 0) ? 1.0 : (placement / distance));
}

int	get_default_color(int z, t_fdf *fdf)
{
    double	percentage;

    percentage = percent(fdf->z_min, fdf->z_max, z);
    if (percentage < 0.2)
        return ((fdf->control->color) ? COLOR_SUN : COLOR_SKY);
    else if (percentage < 0.4)
        return ((fdf->control->color) ? COLOR_ACID_GR : COLOR_BLOOD);
    else if (percentage < 0.6)
        return ((fdf->control->color) ? COLOR_GREEN : COLOR_FLAMINGO);
    else if (percentage < 0.8)
        return ((fdf->control->color) ? COLOR_SKY : COLOR_JAFFA);
    else
        return ((fdf->control->color) ? COLOR_WATER : COLOR_ORANGE);
}

int	get_light(int start, int end, double percentage)
{
    return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(t_point current, t_point start, t_point end, t_point delta)
{
    int		red;
    int		green;
    int		blue;
    double	percentage;

    if (current.color == end.color)
        return (current.color);
    if (delta.x > delta.y)
        percentage = percent(start.x, end.x, current.x);
    else
        percentage = percent(start.y, end.y, current.y);
    red = get_light((start.color >> 16) & 0xFF,
                    (end.color >> 16) & 0xFF,
                    percentage);
    green = get_light((start.color >> 8) & 0xFF,
                      (end.color >> 8) & 0xFF,
                      percentage);
    blue = get_light(start.color & 0xFF,
                     end.color & 0xFF,
                     percentage);
    return ((red << 16) | (green << 8) | blue);
}