/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/26 21:56:09 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		rotate_x(int *y, int *z, double alf)
{
	int			previous_y;

	previous_y = *y;
	*y = previous_y * cos(alf) + *z * sin(alf);
	*z = -previous_y * sin(alf) + *z * cos(alf);
}

/*
** Rotate coordinate by y axis
*/

static void		rotate_y(int *x, int *z, double bet)
{
	int			previous_x;

	previous_x = *x;
	*x = previous_x * cos(bet) + *z * sin(bet);
	*z = -previous_x * sin(bet) + *z * cos(bet);
}

/*
** Rotate coordinate by z axis
*/

static void		rotate_z(int *x, int *y, double gam)
{
	int			previous_x;
	int			previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gam) - previous_y * sin(gam);
	*y = previous_x * sin(gam) + previous_y * cos(gam);
}

/*
** Convert coordinate to iso projection
*/

static void		iso(int *x, int *y, int z)
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
** move: перемещение карты с помощью стрелок
*/

t_point			project(t_point p, t_fdf *fdf)
{
	p.x *= fdf->control->zoom;
	p.y *= fdf->control->zoom;
	p.z *= fdf->control->zoom / fdf->control->z_altitude;
	p.x -= (fdf->width * fdf->control->zoom) / 2;
	p.y -= (fdf->height * fdf->control->zoom) / 2;
	rotate_x(&p.y, &p.z, fdf->control->alf);
	rotate_y(&p.x, &p.z, fdf->control->bet);
	rotate_z(&p.x, &p.y, fdf->control->gam);
	if (fdf->control->projection)
		iso(&p.x, &p.y, p.z);
	p.x += WIDTH / 2 + fdf->control->x_move;
	p.y += (HEIGHT + fdf->height * fdf->control->zoom) / 2
		+ fdf->control->y_move;
	return (p);
}
