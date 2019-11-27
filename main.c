/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/26 21:19:39 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "utils.h"

/*
** mlx_init: даёт соединение между программным обеспечением и дисплеем
** mlx_new_window: создает новое окно на экране, используя параметры size_x
** и size_y, fdf->mlx - это идентификатор соединения
** mlx_new_image: позволяет манипулировать изображениями
** mlx_get_data_addr: возвращает информацию о созданном изображении.
** bits_per_pixel заполнется количеством битов для представления цвета пикселя
** size_line: кол-во байтов для хранения одной строки изображения в памяти
** endian: нужно сохранять цвет пикселя в изображении с прямым порядком байтов
** (endian == 0) или с прямым порядком байтов (endian == 1).
*/

t_fdf			*ft_mymlx_init(t_fdf *fdf)
{
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
	return (fdf);
}

/*
** mlx_loop программа получает «события» от клавиатуры или мыши. Эта функция
** никогда не возвращается. Это бесконечный цикл, который ожидает события,
** а затем вызывает пользовательскую функцию, связанную с этим событием.
** Необходим один параметр - идентификатор соединения mlx_ptr
*/

void			ft_setup_key_hook(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 0, key_press, fdf);
	mlx_hook(fdf->win, 4, 0, ft_mouse_press, fdf);
	mlx_hook(fdf->win, 5, 0, ft_mouse_not_press, fdf);
	mlx_hook(fdf->win, 6, 0, ft_mouse_move, fdf);
}

/*
** Программа принимает только одну карту в качестве аргумента.
** Инициализация структуры fdf и чтение файла через файловый дескриптор.
** Инициализация функций библиотеки mlx, заполнение окна пикселями.
** Подключение событий клавиатуры/мыши.
*/

int				main(int argc, char **argv)
{
	int			fd;
	t_coord		*c_stack;
	t_fdf		*fdf;

	c_stack = NULL;
	if (argc != 2)
		fdf_exit(ERR_USAGE);
	if (!((fd = open(argv[1], O_RDONLY)) >= 0))
		fdf_exit(ERR_MAP);
	if (!(fdf = fdf_init()) || read_map(fd, &c_stack, fdf) == -1)
		fdf_exit(ERR_MAP_READING);
	ft_mymlx_init(fdf);
	ft_draw(fdf);
	ft_setup_key_hook(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
