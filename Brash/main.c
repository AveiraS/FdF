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

int		main(int argc, char **argv)
{
    int			fd;
    t_map		*map;
    t_coord	*coords_stack;
    t_fdf		*fdf;

    errno = 0;
    coords_stack = NULL;

 if (!((fd = open("../maps/42.fdf", O_RDONLY)) >= 0))

      // if (!((fd = open("../maps/mars.fdf", O_RDONLY)) >= 0))
     // if (!((fd = open("../maps/julia.fdf", O_RDONLY)) >= 0))
        fdf_exit(ERR_MAP);
        if (!(map = map_init()) || read_map(fd, &coords_stack, map) == -1)
            fdf_exit(ERR_MAP_READING);
        fdf = fdf_init(map);
        fdf->control = control_init(fdf);
        draw(fdf->map, fdf);
        setup_controls(fdf);
        mlx_loop(fdf->mlx);
    return (0);
}