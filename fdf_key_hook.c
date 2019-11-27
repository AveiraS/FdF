/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/27 14:48:34 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "utils.h"

/*
** Приближение/отдаление фигуры с помощью клавиатуры +(-) или колёсика мыши
*/

void	zoom(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_PLUS || key == MOUSE_SCROLL_UP)
		fdf->control->zoom++;
	else if (key == NUM_PAD_MINUS || key == MOUSE_SCROLL_DOWN)
		fdf->control->zoom--;
	if (fdf->control->zoom < 1)
		fdf->control->zoom = 1;
	ft_draw(fdf);
}

/*
** Перемещение по карте с помощью стрелок на клавиатуре. Смена цвета.
*/

void	move_or_color(int key, t_fdf *fdf)
{
	if (key == MAIN_PAD_C)
		fdf->control->menu ? (fdf->control->menu = 0)
			: (fdf->control->menu = 1);
	else if (key == NUM_PAD_0)
		fdf->control->color = 1;
	else if (key == NUM_PAD_5)
		fdf->control->color = 0;
	else if (key == ARROW_LEFT)
		fdf->control->x_move -= 10;
	else if (key == ARROW_RIGHT)
		fdf->control->x_move += 10;
	else if (key == ARROW_UP)
		fdf->control->y_move -= 10;
	else
		fdf->control->y_move += 10;
	ft_draw(fdf);
}

/*
** Поворот фигуры
*/

void	change_rotation(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_2)
		fdf->control->alf += 0.05;
	else if (key == NUM_PAD_8)
		fdf->control->alf -= 0.05;
	else if (key == NUM_PAD_4)
		fdf->control->bet -= 0.05;
	else if (key == NUM_PAD_6)
		fdf->control->bet += 0.05;
	else if (key == MAIN_PAD_MORE)
		fdf->control->gam += 0.05;
	else if (key == MAIN_PAD_LESS)
		fdf->control->gam -= 0.05;
	ft_draw(fdf);
}

/*
** Изменение параметра z. Управление вершинами(глубиной) карты
*/

void	change_pike(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_STAR)
		fdf->control->z_altitude -= 0.2;
	else if (key == NUM_PAD_SLASH)
		fdf->control->z_altitude += 0.2;
	if (fdf->control->z_altitude < 0.2)
		fdf->control->z_altitude = 0.2;
	else if (fdf->control->z_altitude > 10)
		fdf->control->z_altitude = 10;
	ft_draw(fdf);
}

/*
** Изменение типа проекции: I - изометрический, P - параллельный
*/

void	change_projection(int key, t_fdf *fdf)
{
	fdf->control->alf = 0;
	fdf->control->bet = 0;
	fdf->control->gam = 0;
	if (key == MAIN_PAD_I)
		fdf->control->projection = 1;
	else if (key == MAIN_PAD_P)
		fdf->control->projection = 0;
	ft_draw(fdf);
}
