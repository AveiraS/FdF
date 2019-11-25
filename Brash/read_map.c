/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/23 16:43:26 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "utils.h"

/*
** Добавляем новую координату в стэк в начало списка.
*/

void			put_new_coords(t_coord **coords_stack, t_coord *new)
{
	if (coords_stack)
	{
		if (new)
			new->next = *coords_stack;
		*coords_stack = new;
	}
}

/*
** Достаём первую (верхнюю) координату стэка.
*/

t_coord			*get_last_coord(t_coord **coords_stack)
{
	t_coord *top;

	top = NULL;
	if (coords_stack && *coords_stack)
	{
		top = *coords_stack;
		*coords_stack = (*coords_stack)->next;
	}
	return (top);
}

/*
** Перекладываем координаты точек в массив coords, а цвета в массив colors.
** Заносим в структуру данные о самой высокой и самой низкой точке на карте.
*/

void			stack_to_arrays(t_coord **coords_stack, t_map *map)
{
	t_coord		*coord;

	map->size = map->width * map->height - 1;
	if ((!(map->coords = (int *)ft_memalloc(sizeof(int) * map->size + 1)))
		|| (!(map->colors = (int *)ft_memalloc(sizeof(int) * map->size + 1))))
		fdf_exit(ERR_MEM_ALLOC);
	while ((coord = get_last_coord(coords_stack)))
	{
		map->coords[map->size] = coord->z;
		map->colors[map->size] = coord->color;
		if (coord->z > map->z_max)
			map->z_max = coord->z;
		if (coord->z < map->z_min)
			map->z_min = coord->z;
		map->size--;
		free(coord);
	}
	map->z_range = map->z_max - map->z_min;
}

/*
** Выделяем память под список t_coord и записываем туда координату параметра 'z'
** - через atoi и цвет, если он был передан, - с помощью atoi_base.
** Если цвет отсвутствует - значение принимается равным '-1'.
*/

static t_coord	*new_coord(char *s)
{
	t_coord		*coord;
	int			ptr;

	ptr = 0;
	if (!(coord = (t_coord *)ft_memalloc(sizeof(t_coord))))
		fdf_exit(ERR_MEM_ALLOC);
	if ((ptr = ft_check_color(s, ptr, 0)) == -1)
		fdf_exit(ERR_MAP);
	coord->z = ft_atoi(s);
	coord->color = ptr ? ft_atoi_base(s + ptr, 16) : -1;
	coord->next = NULL;
	return (coord);
}

/*
** Считываем построчно файл с помощью get_next_line, обрезаем пробельные символы
** через strsplit. Из полученного двумерного массива по одному аргументу
** вынимаем координаты 'z'. Получаем стэк из координат вершин и стэк для цвета.
*/

int				read_map(const int fd, t_coord **coords_stack, t_map *map)
{
	char		*line;
	int			result;
	char		**coords;
	int			i;

	while ((result = get_next_line(fd, &line)) == 1)
	{
		if (!(coords = ft_strsplit(line, ' ')))
			fdf_exit(ERR_MAP_READING);
		i = -1;
		while (coords[++i])
			put_new_coords(coords_stack, new_coord((coords[i])));
		if (map->height == 0)
			map->width = i;
		if (map->width != ft_wordcount(line, ' '))
			fdf_exit(ERR_MAP);
		ft_clear_mass(&coords);
		ft_strdel(&line);
		map->height++;
	}
	if (!(*coords_stack))
		fdf_exit(ERR_MAP);
	stack_to_arrays(coords_stack, map);
	return (result);
}
