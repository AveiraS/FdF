/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_give_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/27 14:48:59 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "utils.h"

/*
** Находим текущую позицию точки между двумя точками с известными цветами.
** Значение позиции должно быть выражено в процентах.
*/

double		ft_get_percent(int start, int end, int current)
{
	if (((double)current == (double)start) || ((double)start == (double)end))
		return (0.0);
	if ((double)current == (double)end)
		return (1.0);
	return (((double)current - (double)start) / ((double)end - (double)start));
}

/*
** Выбирается цвет текущего пикселя в зависимости от положения точки
** относительно минимального и максимального значения координаты z.
*/

int			ft_get_default_color(int z, t_fdf *fdf)
{
	double	percent;

	percent = ft_get_percent(fdf->z_min, fdf->z_max, z);
	if (percent < 0.2)
		return ((fdf->control->color) ? COLOR_SUN : COLOR_SKY);
	else if (percent < 0.4)
		return ((fdf->control->color) ? COLOR_ACID_GR : COLOR_BLOOD);
	else if (percent < 0.6)
		return ((fdf->control->color) ? COLOR_GREEN : COLOR_PINK);
	else if (percent < 0.8)
		return ((fdf->control->color) ? COLOR_SKY : COLOR_JAFFA);
	else
		return ((fdf->control->color) ? COLOR_WATER : COLOR_ORANGE);
}

/*
** F(x) = ax + b: линейная интерполяция между двумя точками с учетом 10 процента
** Мы не делаем: (start + percent * (end - start)), потому что если
** начало и конец существенно различаются по величине, тогда мы теряем точность.
*/

int			ft_line_interpol(int start, int end, double percent)
{
	if (start == end)
		return (start);
	return ((int)((1 - percent) * start + percent * end));
}

/*
** get_color - генерирует промежуточный цвет между двумя точками.
** Цвета хранятся в следующем шестнадцатеричном формате:
**	0 x |  F F  |   F F   |  F F  |
**	    |  red  |  green  | blue  |
** Альфа-канал цвета не поддерживается minilibx.
** Нам нужно замаскировать и изолировать каждый цветовой канал, используя сдвиг
** битов и выполнить линейную интерполяцию на каждом канале. Канал 8 бит.
** Эта функция необходима для создания линейного градиента.
*/

int			f_color(t_point cur, t_point start, t_point end, t_point d)
{
	int		red;
	int		green;
	int		blue;
	double	percent;

	if (cur.color == end.color)
		return (cur.color);
	if (d.x > d.y)
		percent = ft_get_percent(start.x, end.x, cur.x);
	else
		percent = ft_get_percent(start.y, end.y, cur.y);
	red = ft_line_interpol((start.color >> 16) & 0xFF,
			(end.color >> 16) & 0xFF, percent);
	green = ft_line_interpol((start.color >> 8) & 0xFF,
			(end.color >> 8) & 0xFF, percent);
	blue = ft_line_interpol(start.color & 0xFF,
			end.color & 0xFF, percent);
	return ((red << 16) | (green << 8) | blue);
}
