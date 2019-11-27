/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:27:28 by pthuy             #+#    #+#             */
/*   Updated: 2019/11/26 21:51:05 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "utils.h"

t_point			new_point(int x, int y, t_fdf *fdf)
{
	t_point		point;
	int			i;

	i = y * fdf->width + x;
	point.x = x;
	point.y = y;
	point.z = fdf->coords[i];
	point.color = (fdf->colors[i] == -1) ?
		ft_get_default_color(point.z, fdf) : fdf->colors[i];
	return (point);
}

/*
** Для macOS endian равно 0, что значит обратный порядок.
** Для цвета эти два формата выглядят так:
** Номер байта	 | 0 | 1 | 2 | 3
** Big Endian	 | 0 | R | B | G
** Little endian | В | G | R | 0
** В формате с прямым порядком байтов -> обратный порядок компонентов цвета:
*/

void			put_pixel(t_fdf *fdf, int x, int y, int color)
{
	int			i;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = x * 4 + y * fdf->size_line;
		fdf->data_addr[i] = color;
		fdf->data_addr[i + 1] = color >> 8;
		fdf->data_addr[i + 2] = color >> 16;
	}
}

/*
** draw_line: алгоритм рисования линий Брезенхема между точкой 1 и 2
** error вычисление отклонения от воображаемой линии между точками.
*/

void			draw_line(t_point p1, t_point p2, t_fdf *fdf, int tmp)
{
	t_point		delta;
	t_point		sign;
	t_point		cur;
	int			error;

	delta.x = FT_ABS(p2.x - p1.x);
	delta.y = FT_ABS(p2.y - p1.y);
	sign.x = p1.x < p2.x ? 1 : -1;
	sign.y = p1.y < p2.y ? 1 : -1;
	error = (delta.x > delta.y ? delta.x : -delta.y) / 2;
	cur = p1;
	while (cur.x != p2.x || cur.y != p2.y)
	{
		put_pixel(fdf, cur.x, cur.y, f_color(cur, p1, p2, delta));
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		tmp = error;
		if (tmp > -delta.x && ((error -= delta.y) || !error))
			cur.x += sign.x;
		if (tmp < delta.y)
		{
			error += delta.x;
			cur.y += sign.y;
		}
	}
}

/*
** data_addr: массив представляет область памяти, где хранится изображение.
** bits_per_pixel: количество бит, используемых для определения цветового
** оттенка пикселя. Истинный цвет иногда называют 24-битным цветом.
** Дополнительный байт (альфа-канал) используется для управления информацией.
** Берём координаты x и y, начиная с 0 и до границ высоты и ширины карты.
** отрисовка карты происходит начиная с левого нижнего угла на право.
*/

void			ft_draw(t_fdf *fdf)
{
	int			x;
	int			y;
	int			*image;
	int			i;

	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	image = (int *)(fdf->data_addr);
	i = -1;
	while (++i < HEIGHT * WIDTH)
		image[i] = BACKGROUND;
	y = -1;
	while (++y < fdf->height)
	{
		x = -1;
		while (++x < fdf->width)
		{
			if (x != fdf->width - 1)
				draw_line(project(x, y, fdf), project(x + 1, y, fdf), fdf, 0);
			if (y != fdf->height - 1)
				draw_line(project(x, y, fdf), project(x, y + 1, fdf), fdf, 0);
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	(fdf->control->menu) ? (print_menu(fdf, 0)) : (fdf->control->menu = 0);
}
