/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/23 16:51:07 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "utils.h"

t_map			*map_init(void)
{
	t_map		*map;

	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
		fdf_exit(ERR_MEM_ALLOC);
	map->width = 0;
	map->height = 0;
	map->coords = NULL;
	map->colors = NULL;
	map->z_min = FT_INT_MAX;
	map->z_max = FT_INT_MIN;
	map->z_range = 0;
	return (map);
}

/*
** mlx_init: даёт соединение между программным обеспечением и дисплеем
** mlx_new_window: создает новое окно на экране, используя параметры size_x
** и size_y, fdf->mlx - это идентификатор соединения
** mlx_new_image: позволяет манипулировать изображениями
** mlx_get_data_addr: возвращает информацию о созданном изображении.
** bits_per_pixel будет заполнен количеством битов, необходимых для представления цвета пикселя
** size_line - количество байтов, используемых для хранения одной строки изображения в памяти.
** endian говорит вам, нужно ли сохранять цвет пикселя в изображении с прямым порядком байтов
** (endian == 0) или с прямым порядком байтов (endian == 1).
*/

t_fdf			*fdf_init(t_map *map)
{
	t_fdf		*fdf;

	if (!(fdf = (t_fdf *)ft_memalloc(sizeof(t_fdf))))
		fdf_exit(ERR_FDF_INIT);
	if (!(fdf->mlx = mlx_init()))
		fdf_exit(ERR_FDF_INIT);
	if (!(fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF")))
		fdf_exit(ERR_FDF_INIT);
	if (!(fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT)))
		fdf_exit(ERR_FDF_INIT);
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel),
			&(fdf->size_line), &(fdf->endian));
	fdf->map = map;
	if (!(fdf->mouse = (t_mouse *)ft_memalloc(sizeof(t_mouse))))
		fdf_exit(ERR_FDF_INIT);
	return (fdf);
}

/*
** Initialize t_camera element
*/

t_control		*control_init(t_fdf *fdf)
{
	t_control	*control;

	if (!(control = (t_control *)ft_memalloc(sizeof(t_control))))
		fdf_exit(ERR_CONTROL);
    control->zoom = FT_MIN((WIDTH - MENU_WIDTH) / fdf->map->width / 2,
			HEIGHT / fdf->map->height / 2);
    control->alpha = 0;
    control->beta = 0;
    control->gamma = 0;
    control->z_divisor = 4;
    control->x_offset = 0;
    control->y_offset = 0;
    control->color = 0;
	return (control);
}
