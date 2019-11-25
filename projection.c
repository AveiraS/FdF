/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/09 14:30:45 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_x(int *y, int *z, double alpha)
{
    int previous_y;

    previous_y = *y;
    *y = previous_y * cos(alpha) + *z * sin(alpha);
    *z = -previous_y * sin(alpha) + *z * cos(alpha);
}

/*
** Rotate coordinate by y axis
*/

static void	rotate_y(int *x, int *z, double beta)
{
    int previous_x;

    previous_x = *x;
    *x = previous_x * cos(beta) + *z * sin(beta);
    *z = -previous_x * sin(beta) + *z * cos(beta);
}

/*
** Rotate coordinate by z axis
*/

static void	rotate_z(int *x, int *y, double gamma)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = previous_x * cos(gamma) - previous_y * sin(gamma);
    *y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

/*
** Convert coordinate to iso projection
*/

static void	iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(RADIAN);
    *y = -z + (previous_x + previous_y) * sin(RADIAN);
}

/*
** control->zoom: увеличение реального размера фигуры, p.z размер высот/низин
** control->zoom / 2: поворот фигуры относительно её середины
** rotate: верчение под любым углом, по соответсутвующим осям xyz
** offset: перемещение карты с помощью стрелок
*/

t_point		project(t_point p, t_fdf *fdf)
{
    p.x *= fdf->control->zoom;
    p.y *= fdf->control->zoom;
    p.z *= fdf->control->zoom / fdf->control->z_divisor;
    p.x -= (fdf->width * fdf->control->zoom) / 2;
    p.y -= (fdf->height * fdf->control->zoom) / 2;
    rotate_x(&p.y, &p.z, fdf->control->alpha);
    rotate_y(&p.x, &p.z, fdf->control->beta);
    rotate_z(&p.x, &p.y, fdf->control->gamma);
    if (fdf->control->projection)
        iso(&p.x, &p.y, p.z);
    p.x += (WIDTH - MENU_WIDTH) / 2 + fdf->control->x_offset + MENU_WIDTH;
    p.y += (HEIGHT + fdf->height * fdf->control->zoom) / 2
           + fdf->control->y_offset;
    return (p);
}
