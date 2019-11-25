/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/09 14:30:45 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "utils.h"
//cc -I /ust/local/include main.c color.c control.c draw.c fdf.h init_struct.c projection.c read_map.c utils.h utils.c libft/libft.a -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

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

int		main(int argc, char **argv)
{
    int			fd;
    t_coord	    *coords_stack;
    t_fdf		*fdf;

    errno = 0;
    coords_stack = NULL;

 if (!((fd = open("../maps/42.fdf", O_RDONLY)) >= 0))

      // if (!((fd = open("../maps/mars.fdf", O_RDONLY)) >= 0))
     // if (!((fd = open("../maps/julia.fdf", O_RDONLY)) >= 0))
        fdf_exit(ERR_MAP);
        if (!(fdf = fdf_init()) || read_map(fd, &coords_stack, fdf) == -1)
            fdf_exit(ERR_MAP_READING);
        if (!(fdf->mlx = mlx_init()))
            fdf_exit(ERR_FDF_INIT);
        if (!(fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF")))
         fdf_exit(ERR_FDF_INIT);
         if (!(fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT)))
            fdf_exit(ERR_FDF_INIT);
        fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel),
                                       &(fdf->size_line), &(fdf->endian));
        if (!(fdf->mouse = (t_mouse *)ft_memalloc(sizeof(t_mouse))))
            fdf_exit(ERR_FDF_INIT);
        fdf->control = control_init(fdf);
        draw(fdf);
        setup_controls(fdf);
        mlx_loop(fdf->mlx);
    return (0);
}