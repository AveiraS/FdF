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

#include "mlx.h"
#include "fdf.h"
#include "utils.h"

/*
** Close window with 'X'
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
    draw(fdf->map, fdf);
}

/*
** Move map
*/

void	move(int key, t_fdf *fdf)
{
    if (key == ARROW_LEFT)
        fdf->control->x_offset -= 10;
    else if (key == ARROW_RIGHT)
        fdf->control->x_offset += 10;
    else if (key == ARROW_UP)
        fdf->control->y_offset -= 10;
    else
        fdf->control->y_offset += 10;
    draw(fdf->map, fdf);
}

/*
** Rotate map
*/

void	rotate(int key, t_fdf *fdf)
{
    if (key == NUM_PAD_2)
        fdf->control->alpha += 0.05;
    else if (key == NUM_PAD_8)
        fdf->control->alpha -= 0.05;
    else if (key == NUM_PAD_4)
        fdf->control->beta -= 0.05;
    else if (key == NUM_PAD_6)
        fdf->control->beta += 0.05;
    else if (key == NUM_PAD_1 || key == NUM_PAD_3)
        fdf->control->gamma += 0.05;
    else if (key == NUM_PAD_7 || key == NUM_PAD_9)
        fdf->control->gamma -= 0.05;
    draw(fdf->map, fdf);
}

/*
** Change z value. Make map more flatten
*/

void	change_color(int key, t_fdf *fdf)
{
    if (key == NUM_PAD_0)
        fdf->control->color = 1;
    else if (key == NUM_PAD_5)
        fdf->control->color = 0;
    draw(fdf->map, fdf);
}

void	change_pike(int key, t_fdf *fdf)
{
    if (key == NUM_PAD_STAR)
        fdf->control->z_divisor -= 0.1;
    else if (key == NUM_PAD_SLASH)
        fdf->control->z_divisor += 0.1;
    if (fdf->control->z_divisor < 0.1)
        fdf->control->z_divisor = 0.1;
    else if (fdf->control->z_divisor > 10)
        fdf->control->z_divisor = 10;
    draw(fdf->map, fdf);
}

/*
** Change projection type
*/

void	change_projection(int key, t_fdf *fdf)
{
    fdf->control->alpha = 0;
    fdf->control->beta = 0;
    fdf->control->gamma = 0;
    if (key == MAIN_PAD_I)
        fdf->control->projection = ISO;
    else if (key == MAIN_PAD_P)
        fdf->control->projection = PARALLEL;
    draw(fdf->map, fdf);
}

int			mouse_press(int button, int x, int y, void *param)
{
    t_fdf	*fdf;

    (void)x;
    (void)y;
    fdf = (t_fdf *)param;
    if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
        zoom(button, fdf);
    else if (button == MOUSE_LEFT_BUTTON)
        fdf->mouse->is_pressed = 1;
    return (0);
}

/*
** Handle mouse release
*/

int			mouse_release(int button, int x, int y, void *param)
{
    t_fdf	*fdf;

    (void)x;
    (void)y;
    (void)button;
    fdf = (t_fdf *)param;
    fdf->mouse->is_pressed = 0;
    return (0);
}

/*
** Handle mouse move
*/

int			mouse_move(int x, int y, void *param)
{
    t_fdf	*fdf;

    fdf = (t_fdf *)param;
    fdf->mouse->previous_x = fdf->mouse->x;
    fdf->mouse->previous_y = fdf->mouse->y;
    fdf->mouse->x = x;
    fdf->mouse->y = y;
    if (fdf->mouse->is_pressed)
    {
        fdf->control->beta += (x - fdf->mouse->previous_x) * 0.002;
        fdf->control->alpha += (y - fdf->mouse->previous_y) * 0.002;
        draw(fdf->map, fdf);
    }
    return (0);
}

int			key_press(int key, void *param)
{
    t_fdf	*fdf;

    fdf = (t_fdf *)param;
    if (key == MAIN_PAD_ESC)
        exit(0);
    if (key == NUM_PAD_PLUS || key == NUM_PAD_MINUS)
        zoom(key, fdf);
    else if (key == NUM_PAD_0 || key == NUM_PAD_5)
        change_color(key, fdf);
    else if (key == ARROW_LEFT || key == ARROW_RIGHT
             || key == ARROW_UP || key == ARROW_DOWN)
        move(key, fdf);
    else if (key == NUM_PAD_1 || key == NUM_PAD_2
             || key == NUM_PAD_3 || key == NUM_PAD_4
             || key == NUM_PAD_6 || key == NUM_PAD_7
             || key == NUM_PAD_8 || key == NUM_PAD_9)
        rotate(key, fdf);
    else if (key == NUM_PAD_STAR || key == NUM_PAD_SLASH)
        change_pike(key, fdf);
    else if (key == MAIN_PAD_P || key == MAIN_PAD_I)
        change_projection(key, fdf);
    return (0);
}
/*
** Connect functions-controllers to window
*/

void	setup_controls(t_fdf *fdf)
{
    mlx_hook(fdf->win, 2, 0, key_press, fdf);
    mlx_hook(fdf->win, 17, 0, close, fdf);
    mlx_hook(fdf->win, 4, 0, mouse_press, fdf);
    mlx_hook(fdf->win, 5, 0, mouse_release, fdf);
    mlx_hook(fdf->win, 6, 0, mouse_move, fdf);
}