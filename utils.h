/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 18:06:25 by asmall            #+#    #+#             */
/*   Updated: 2019/11/26 22:10:10 by asmall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define FT_MIN(A, B) (((A) < (B)) ? (A) : (B))
# define FT_MAX(A, B) (((A) > (B)) ? (A) : (B))
# define FT_ABS(X) (((X) < 0) ? (-(X)) : (X))

# define FT_INT_MAX			((int)2147483647)
# define FT_INT_MIN			((int)-2147483648)

# define TEXT_COLOR			0x000000
# define BACKGROUND			0xFFFFFF
# define MENU_BACKGROUND	0x000000

# define COLOR_WATER		0x00F7FF
# define COLOR_GREEN		0x00FF00
# define COLOR_SUN			0xF3FF00
# define COLOR_SKY			0x14FCF2
# define COLOR_BLOOD		0xFF0000
# define COLOR_PINK			0xEC4B27
# define COLOR_JAFFA		0xEF8633
# define COLOR_ORANGE		0xF3AF3D
# define COLOR_ACID_GR		0x80FF00

# define ERR_USAGE			"Usage: ./fdf source_file"
# define ERR_MAP			"Incorrect MAP_FILE"
# define ERR_MAP_READING	"Reading error"
# define ERR_FDF_INIT		"FdF initialization error"
# define ERR_CONTROL		"Control initialization error"
# define ERR_MEM_ALLOC		"FdF: failed to allocate memory\n"

# define MOUSE_LEFT_BUTTON	1
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# define ARROW_UP			126
# define ARROW_DOWN			125
# define ARROW_LEFT			123
# define ARROW_RIGHT		124

# define NUM_PAD_0			82
# define NUM_PAD_2			84
# define NUM_PAD_4			86
# define NUM_PAD_5			87
# define NUM_PAD_6			88
# define NUM_PAD_8			91
# define NUM_PAD_PLUS		69
# define NUM_PAD_MINUS		78
# define NUM_PAD_STAR		67
# define NUM_PAD_SLASH		75
# define MAIN_PAD_LESS		43
# define MAIN_PAD_MORE		47
# define MAIN_PAD_ESC		53
# define MAIN_PAD_I			34
# define MAIN_PAD_P			35
# define MAIN_PAD_C			8

#endif
