/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 18:47:33 by cwu               #+#    #+#             */
/*   Updated: 2018/05/05 18:47:38 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int color(int st, int end, float t)
{
	int r;
	int g;
	int b;

	r = (int)((1.0 - t) * (st >> 16) + t * (end >> 16));
	g = (int)((1.0 - t) * ((st >> 8) & 255) + t * ((end >> 8) & 255));
	b = (int)((1.0 - t) * (st & 255) + t * (end & 255));
	return ((r << 16) + (g << 8) + b);
}

int hcolor(int input)
{
	float h;

	h = 1;
	if (g_e.y - g_e.x > 0)
		h = g_e.y - g_e.x;
	return(color(g_mincolor, g_maxcolor, (float)abs(input) / h));
}

t_pt project(int x, int y, int z)
{
	t_pt p2;
	int x2;
	int y2;

	x2 = cos(g_ang) * x - sin(g_ang) * y;
	y2 = sin(g_ang) * x + cos(g_ang) * y;
	p2.x = (int)(sqrt(3) / 2 * (x2 + y2)) + 750;
	p2.y = (int)(x2 - y2) / 2 - 2 * z + 750;
	return (p2);
}

void d_line(t_pt a, t_pt b, int h1, int h2)
{
	t_pt l;
	int i;
	float d;
	int ch1;
	int ch2;

	ch1 = hcolor(h1);
	ch2 = hcolor(h2);
	l.x = b.x - a.x;
	l.y = b.y - a.y;
	i = -1;
	if (abs(l.x) >= abs(l.y))
		while (++i < abs(l.x))
		{
			d = (float)i / l.x;
			PIX(g_mp, g_wp, a.x + copysign(i, l.x), a.y + copysign(round(d * l.y), l.y),
				color(ch1, ch2, fabsf(d)));
		}
	else
		while (++i < abs(l.y))
		{
			d = (float)i / l.y;
			PIX(g_mp, g_wp, a.x + copysign(round(d * l.x), l.x), a.y + copysign(i, l.y),
				color(ch1, ch2, fabsf(d)));
		}
}

void connect(int c1, int r1, int c2, int r2)
{
	d_line(project(g_sc * (c1 - g_mw / 2), g_sc * (r1 - g_mh / 2), g_s[r1][c1]),
	project(g_sc * (c2 - g_mw / 2), g_sc * (r2 - g_mh / 2), g_s[r2][c2]),
	g_in[r1][c1], g_in[r2][c2]);
}
