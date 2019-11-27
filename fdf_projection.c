/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_projection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/27 14:44:53 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** fdf->control->alf: поворот координаты по оси х
** fdf->control->bet: поворот координаты по оси y
** fdf->control->gam: поворот координаты по оси z
*/

void			ft_rotate_xyz(int *y, int *z, int *x, t_fdf *fdf)
{
	int			prev_y;
	int			prev_x;

	prev_y = *y;
	prev_x = *x;
	if (fdf->control->alf)
	{
		*y = prev_y * cos(fdf->control->alf) + *z * sin(fdf->control->alf);
		*z = -prev_y * sin(fdf->control->alf) + *z * cos(fdf->control->alf);
	}
	if (fdf->control->bet)
	{
		*x = prev_x * cos(fdf->control->bet) + *z * sin(fdf->control->bet);
		*z = -prev_x * sin(fdf->control->bet) + *z * cos(fdf->control->bet);
	}
	if (fdf->control->gam)
	{
		prev_x = *x;
		prev_y = *y;
		*x = prev_x * cos(fdf->control->gam) - prev_y * sin(fdf->control->gam);
		*y = prev_x * sin(fdf->control->gam) + prev_y * cos(fdf->control->gam);
	}
}

/*
** Истинная изометрическая проекция использует угол 30° (0,523599 рад).
** Изометрическая проекция 2:1 использует угол 26,57° (0,46373398 рад).
*/

void			ft_iso(int *x, int *y, int z)
{
	int			prev_x;
	int			prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = (prev_x - prev_y) * cos(RADIAN);
	*y = -z + (prev_x + prev_y) * sin(RADIAN);
}

/*
** производим манипуляции с текущими координатами:
** control->zoom: увеличение реального размера фигуры, p.z размер высот/низин
** control->zoom / 2: поворот фигуры относительно её середины
** rotate_xyz: верчение под любым углом, по соответсутвующим осям xyz
** move: перемещение карты с помощью стрелок
*/

t_point			project(int x, int y, t_fdf *fdf)
{
	t_point		p;

	p = new_point(x, y, fdf);
	p.x *= fdf->control->zoom;
	p.y *= fdf->control->zoom;
	p.z *= fdf->control->zoom / fdf->control->z_altitude;
	p.x -= (fdf->width * fdf->control->zoom) / 2;
	p.y -= (fdf->height * fdf->control->zoom) / 2;
	ft_rotate_xyz(&p.x, &p.y, &p.z, fdf);
	if (fdf->control->projection)
		ft_iso(&p.x, &p.y, p.z);
	p.x += WIDTH / 2 + fdf->control->x_move;
	p.y += (HEIGHT + fdf->height * fdf->control->zoom) / 2
		+ fdf->control->y_move;
	return (p);
}
