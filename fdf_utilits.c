/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/26 22:02:44 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"
#include "utils.h"

void		fdf_exit(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

/*
** Проверяем наличие ',' в переданном значение и валидность параметров,
** в случае, если ',' была найдена. Возвращаем указатель на первый символ
** после запятой.
*/

int			ft_check_color(const char *str, int ptr, int i)
{
	int		count;

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

void		print_menu(t_fdf *fdf, int y)
{
	void	*mlx;
	void	*win;

	mlx = fdf->mlx;
	win = fdf->win;
	mlx_string_put(mlx, win, 65, y += 20, TEXT_COLOR, "How to Use");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Press ESC to quite");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Zoom: Scroll or +/-");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Move: Arrows");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Pikes: * or /");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Change color: 5/0");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Rotate: Press & Move");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Rotate:");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Rotate x - 2/8");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Rotate y - 4/6");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Rotate z - </>");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Projection");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "ISO: press I ");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Parallel: press P");
}
