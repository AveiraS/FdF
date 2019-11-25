/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/22 18:12:01 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

void	fdf_exit(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

t_point	new_point(int x, int y, t_map *map, t_fdf *fdf)
{
	t_point	point;
	int		i;

    i = y * map->width + x;
    point.x = x;
    point.y = y;
    point.z = map->coords[i];
    point.color = (map->colors[i] == -1) ?
                  get_default_color(point.z, map, fdf) : map->colors[i];
    return (point);
}

/*
** Проверяем наличие ',' в переданном значение и валидность параметров,
** в случае, если ',' была найдена. Возвращаем указатель на первый символ
** после запятой.
*/

int				ft_check_color(const char *str, int ptr, int i)
{
    int			count;

    count = 0;
    while (str[i] && str[i] != ',')
    {
        if (str[i] == '-' || str[i] == '+')
            i++;
        if (!ft_isdigit(str[i]))
            return (-1);
        i++;
    }
    if (str[i] == ',')
    {
        ptr = i + 1;
        while (str[++i])
        {
            if ((str[i] > 102 && str[i] != 'x') || (str[i] < 48 && str[i] != 44)
                || (str[i] < 65 && str[i] > 57) || (str[i] > 70 && str[i] < 97))
                return (-1);
            count++;
        }
    }
    if (count >= 9)
        return (-1);
    return (ptr);
}