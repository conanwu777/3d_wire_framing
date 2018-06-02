/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 18:48:00 by cwu               #+#    #+#             */
/*   Updated: 2018/05/05 18:48:04 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# define PIX mlx_pixel_put

typedef struct	s_pt
{
	int			x;
	int			y;
}				t_pt;

void			*g_mp;
void			*g_wp;
int				**g_in;
int				**g_s;
int				g_mw;
int				g_mh;
int				g_sc;
int				g_height;
int				g_mincolor;
int				g_maxcolor;
float			g_ang;
t_pt			g_c;
t_pt			g_e;
t_pt			g_offset;

int				numline(int fd);
void			getinput(int fd, char *str);
int				free_and_exit(void);
void			scaleheight(int n);
int				color(int st, int end, float t);
int				hcolor(int input);
t_pt			project(int x, int y, int z);
void			d_line(t_pt a, t_pt b, int h1, int h2);
void			connect(int c1, int r1, int c2, int r2);
int				color_adjust(int key);

#endif
