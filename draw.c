/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 19:27:28 by asmall            #+#    #+#             */
/*   Updated: 2019/11/09 19:27:32 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "utils.h"

t_point	new_point(int x, int y, t_fdf *fdf)
{
    t_point	point;
    int		i;

    i = y * fdf->width + x;
    point.x = x;
    point.y = y;
    point.z = fdf->coords[i];
    point.color = (fdf->colors[i] == -1) ?
                  get_default_color(point.z,fdf) : fdf->colors[i];
    return (point);
}

/*
** Put pixel into map image
*/

static void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
    int		i;

    if (x >= MENU_WIDTH && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
        fdf->data_addr[i] = color;
        fdf->data_addr[i + 1] = color >> 8;
        fdf->data_addr[i + 2] = color >> 16;
    }
}

/*
** Draw line f s
*/

static void	draw_line(t_point p1, t_point p2, t_fdf *fdf)
{
    t_point	delta;
    t_point	sign;
    t_point	cur;
    int		error;
    int     e2;

    delta.x = FT_ABS(p2.x - p1.x);
    delta.y = FT_ABS(p2.y - p1.y);
    sign.x = p1.x < p2.x ? 1 : -1;
    sign.y = p1.y < p2.y ? 1 : -1;
    error = (delta.x > delta.y ? delta.x : -delta.y) / 2;
    cur = p1;
    while (cur.x != p2.x || cur.y != p2.y)
    {
        put_pixel(fdf, cur.x, cur.y, get_color(cur, p1, p2, delta));
        if (p1.x == p2.x && p1.y == p2.y)
            break ;
        e2 = error;
        if (e2 > -delta.x && ((error -= delta.y) || !error))
            cur.x += sign.x;
        if (e2 < delta.y)
        {
            error += delta.x;
            cur.y += sign.y;
        }
    }
}

/*
** data_addr: массив представляет область памяти, в которой хранится изображение.
** Заполняем массив выбранными цветами для закрашивания карты и меню управления.
*/

static void	draw_background(t_fdf *fdf)
{
    int	*image;
    int	i;

    ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
    image = (int *)(fdf->data_addr);
    i = 0;
    while (i < HEIGHT * WIDTH)
    {
        image[i] = (i % WIDTH < MENU_WIDTH) ? MENU_BACKGROUND : BACKGROUND;
        i++;
    }
}

/*
** Применяется алгоритм Брезенхейма
*/

void		draw(t_fdf *fdf)
{
    int		x;
    int		y;

    draw_background(fdf);
    y = 0;
    while (y < fdf->height)
    {
        x = 0;
        while (x < fdf->width)
        {
            if (x != fdf->width - 1)
                draw_line(project(new_point(x, y,fdf), fdf),
                          project(new_point(x + 1, y, fdf), fdf), fdf);
            if (y != fdf->height - 1)
                draw_line(project(new_point(x, y, fdf), fdf),
                          project(new_point(x, y + 1, fdf), fdf), fdf);
            x++;
        }
        y++;
    }
    mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
    print_menu(fdf, 0);
}
