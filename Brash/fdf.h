/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fhf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/09 14:30:45 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

#include "./minilibx_macos/mlx.h"
#include "./libft/libft.h"
#include "math.h"
#include <errno.h>

/*
** math.h - для выполнения простых математических операций.
** errno.h - содержит объявление макроса для идентификации ошибок через их код.
*/

# define HEIGHT			1080
# define WIDTH			1920
# define MENU_WIDTH		250

typedef enum
{
    ISO,
    PARALLEL
}	t_projection;

typedef struct			s_coord
{
    int					z;
    int					color;
    struct s_coord      *next;
}						t_coord;

typedef struct			s_point
{
    int					x;
    int					y;
    int					z;
    int					color;
}						t_point;

typedef struct			s_control
{
    t_projection		projection;
    int					zoom;
    double				alpha;
    double				beta;
    double				gamma;
    float				z_divisor;
    int					x_offset;
    int					y_offset;
    int                 color;
}						t_control;

typedef struct			s_map
{
    int					width;
    int					height;
    int					*coords;
    int					*colors;
    int					z_min;
    int					z_max;
    int					z_range;
    size_t              size;
}						t_map;

typedef struct			s_mouse
{
    char				is_pressed;
    int					x;
    int					y;
    int					previous_x;
    int					previous_y;
}						t_mouse;

typedef struct			s_fdf
{
    void				*mlx;
    void				*win;
    void				*img;
    char				*data_addr;
    int					bits_per_pixel;
    int					size_line;
    int					endian;
    t_control   		*control;
    t_map				*map;
    t_mouse				*mouse;
}						t_fdf;

//read_map.c
int					    read_map(const int fd, t_coord **coords_stack, t_map *map);

//utils
void	                fdf_exit(char *s);
t_point	new_point(int x, int y, t_map *map, t_fdf *fdf);
int				ft_check_color(const char *str, int ptr, int i);

//init
t_map		            *map_init(void);
t_control	            *control_init(t_fdf *fdf);
t_fdf		            *fdf_init(t_map *map);

//create_map
void		            stack_to_arrays(t_coord **coords_stack, t_map *map);

//draw
void	               	draw(t_map *map, t_fdf *fdf);

//proection
t_point		            project(t_point p, t_fdf *fdf);

//color
int	get_default_color(int z, t_map *map, t_fdf *fdf);
int                    	get_color(t_point current, t_point start, t_point end, t_point delta);

//control
void	setup_controls(t_fdf *fdf);

#endif
