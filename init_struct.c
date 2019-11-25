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

t_fdf			*fdf_init(void)
{
	t_fdf		*fdf;

	if (!(fdf = (t_fdf *)ft_memalloc(sizeof(t_fdf))))
		fdf_exit(ERR_MEM_ALLOC);
	fdf->width = 0;
	fdf->height = 0;
	fdf->coords = NULL;
	fdf->colors = NULL;
	fdf->z_min = FT_INT_MAX;
	fdf->z_max = FT_INT_MIN;
	fdf->z_range = 0;
	return (fdf);
}

/*
** zoom:
*/

t_control		*control_init(t_fdf *fdf)
{
	t_control	*control;

	if (!(control = (t_control *)ft_memalloc(sizeof(t_control))))
		fdf_exit(ERR_CONTROL);
    control->zoom = FT_MIN((WIDTH - MENU_WIDTH) / fdf->width / 2,
			HEIGHT / fdf->height / 2);
    control->alpha = 0;
    control->beta = 0;
    control->gamma = 0;
    control->projection = 1;
    control->z_divisor = 4;
    control->x_offset = 0;
    control->y_offset = 0;
    control->color = 0;
	return (control);
}
