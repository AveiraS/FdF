/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/09 14:30:45 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "utils.h"

/*
** Приближение/отдаление фигуры с помощью клавиатуры +(-) или колёсика мыши
*/

void	zoom(int key, t_fdf *fdf)
{
    if (key == NUM_PAD_PLUS ||
        key == MOUSE_SCROLL_UP)
        fdf->control->zoom++;
    else if (key == NUM_PAD_MINUS ||
             key == MOUSE_SCROLL_DOWN)
        fdf->control->zoom--;
    if (fdf->control->zoom < 1)
        fdf->control->zoom = 1;
    draw(fdf);
}

/*
** Перемещение по карте с помощью стрелок на клавиатуре. Смена цвета.
*/

void	move_or_color(int key, t_fdf *fdf)
{
    if (key == NUM_PAD_0)
        fdf->control->color = 1;
    else if (key == NUM_PAD_5)
        fdf->control->color = 0;
    else if (key == ARROW_LEFT)
        fdf->control->x_offset -= 10;
    else if (key == ARROW_RIGHT)
        fdf->control->x_offset += 10;
    else if (key == ARROW_UP)
        fdf->control->y_offset -= 10;
    else
        fdf->control->y_offset += 10;
    draw(fdf);
}

/*
** Поворот фигуры
*/

void	change_rotation(int key, t_fdf *fdf)
{
    if (key == NUM_PAD_2)
        fdf->control->alpha += 0.05;
    else if (key == NUM_PAD_8)
        fdf->control->alpha -= 0.05;
    else if (key == NUM_PAD_4)
        fdf->control->beta -= 0.05;
    else if (key == NUM_PAD_6)
        fdf->control->beta += 0.05;
    else if (key == MAIN_PAD_MORE)
        fdf->control->gamma += 0.05;
    else if (key == MAIN_PAD_LESS)
        fdf->control->gamma -= 0.05;
    draw(fdf);
}

/*
** Изменение параметра z. Управление вершинами(глубиной) карты
*/

void	change_pike(int key, t_fdf *fdf)
{
    if (key == NUM_PAD_STAR)
        fdf->control->z_divisor -= 0.2;
    else if (key == NUM_PAD_SLASH)
        fdf->control->z_divisor += 0.2;
    if (fdf->control->z_divisor < 0.2)
        fdf->control->z_divisor = 0.2;
    else if (fdf->control->z_divisor > 10)
        fdf->control->z_divisor = 10;
    draw(fdf);
}

/*
** Изменение типа проекции: I - изометрический, P - параллельный
*/

void	change_projection(int key, t_fdf *fdf)
{
    fdf->control->alpha = 0;
    fdf->control->beta = 0;
    fdf->control->gamma = 0;
    if (key == MAIN_PAD_I)
        fdf->control->projection = 1;
    else if (key == MAIN_PAD_P)
        fdf->control->projection = 0;
    draw(fdf);
}

/*
** Управление вводом ключей с клавиатуры (подробнее читай утилиты)
*/

int			key_press(int key, void *param)
{
    t_fdf	*fdf;

    fdf = (t_fdf *)param;
    if (key == MAIN_PAD_ESC)
        exit(0);
    if (key == NUM_PAD_PLUS || key == NUM_PAD_MINUS)
        zoom(key, fdf);
    else if (key == ARROW_LEFT || key == ARROW_RIGHT
             || key == ARROW_UP || key == ARROW_DOWN
             || key == NUM_PAD_0 || key == NUM_PAD_5)
        move_or_color(key, fdf);
    else if (key == MAIN_PAD_LESS || key == MAIN_PAD_MORE
             || key == NUM_PAD_4 || key == NUM_PAD_6
             || key == NUM_PAD_2 || key == NUM_PAD_8)
        change_rotation(key, fdf);
    else if (key == NUM_PAD_STAR || key == NUM_PAD_SLASH)
        change_pike(key, fdf);
    else if (key == MAIN_PAD_P || key == MAIN_PAD_I)
        change_projection(key, fdf);
    return (0);
}
/*
** Подключение функций-контроллеров к окну
*/

void	setup_controls(t_fdf *fdf)
{
    mlx_hook(fdf->win, 2, 0, key_press, fdf);
    mlx_hook(fdf->win, 4, 0, mouse_press, fdf);
    mlx_hook(fdf->win, 5, 0, mouse_release, fdf);
    mlx_hook(fdf->win, 6, 0, mouse_move, fdf);
}