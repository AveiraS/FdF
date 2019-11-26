/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fhf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 14:30:43 by asmall            #+#    #+#             */
/*   Updated: 2019/11/26 22:46:04 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./minilibx_macos/mlx.h"
# include "./libft/libft.h"
# include "math.h"
# include <errno.h>

/*
** math.h - для выполнения простых математических операций.
** errno.h - содержит объявление макроса для идентификации ошибок через их код.
*/

# define RADIAN		0.523599
# define HEIGHT		1080
# define WIDTH		1920

typedef struct		s_coord
{
	int				z;
	int				color;
	struct s_coord	*next;
}					t_coord;

typedef struct		s_point
{
	int				x;
	int				y;
	int				z;
	int				color;
}					t_point;

typedef struct		s_control
{
	int				projection;
	int				zoom;
	double			alf;
	double			bet;
	double			gam;
	float			z_altitude;
	int				x_move;
	int				y_move;
	int				color;
	int				menu;
}					t_control;

typedef struct		s_mouse
{
	char			is_pressed;
	int				x;
	int				y;
	int				previous_x;
	int				previous_y;
}					t_mouse;

typedef struct		s_fdf
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				width;
	int				height;
	int				*coords;
	int				*colors;
	int				z_min;
	int				z_max;
	size_t			size;
	t_control		*control;
	t_mouse			*mouse;
}					t_fdf;

/*
** main.c управление окнами и библиотекой minilibx
*/

t_fdf				*ft_mymlx_init(t_fdf *fdf);
void				setup_key_hook(t_fdf *fdf);

/*
** fdf_init_struct.c инициализация структуры fdf и control
*/

t_fdf				*fdf_init(void);
t_control			*control_init(t_fdf *fdf);

/*
** fdf_read_map.c чтение карты и заполнение массивов intов
*/

int					read_map(const int fd, t_coord **c_stack, t_fdf *fdf);
void				stack_to_arrays(t_coord **coords_stack, t_fdf *fdf);
void				put_new_coords(t_coord **coords_stack, t_coord *new);
t_coord				*get_last_coord(t_coord **coords_stack);
static t_coord		*new_coord(char *s);

/*
** fdf_key_hook.c контроль управления через клавиатуру
*/

int					key_press(int key, void *param);
void				change_projection(int key, t_fdf *fdf);
void				change_pike(int key, t_fdf *fdf);
void				change_rotation(int key, t_fdf *fdf);
void				move_or_color(int key, t_fdf *fdf);
void				zoom(int key, t_fdf *fdf);

/*
** fdf_mouse.c контроль управления с помощью мыши
*/

int					mouse_press(int button, int x, int y, void *param);
int					mouse_release(int button, int x, int y, void *param);
int					mouse_move(int x, int y, void *param);

/*
** fdf_draw_map.c отрисовка пиксельный линий в окно
*/

void				draw(t_fdf *fdf);
static void			draw_background(t_fdf *fdf);
static void			draw_line(t_point p1, t_point p2, t_fdf *fdf);
static void			put_pixel(t_fdf *fdf, int x, int y, int color);
t_point				new_point(int x, int y, t_fdf *fdf);

/*
** fdf_give_color.c отрисовка пиксельный линий в окно
*/

int					f_color(t_point cur, t_point start, t_point end, t_point d);
int					ft_line_interpol(int start, int end, double percent);
int					get_default_color(int z, t_fdf *fdf);
double				ft_get_percent(int start, int end, int current);

/*
** fdf_projection.c регулировка положения карты в окне
*/

t_point				project(t_point p, t_fdf *fdf);
static void			iso(int *x, int *y, int z);
static void			rotate_z(int *x, int *y, double gam);
static void			rotate_y(int *x, int *z, double bet);
static void			rotate_x(int *y, int *z, double alf);

/*
** fdf_utilits.c дополнительные функции, отрисовка меню управления
*/

void				fdf_exit(char *s);
void				print_menu(t_fdf *fdf, int y);
int					ft_check_color(const char *str, int ptr, int i);
#endif
