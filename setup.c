/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 18:47:12 by cwu               #+#    #+#             */
/*   Updated: 2018/05/05 18:47:17 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		color_adjust(int key)
{
	if (key == 15 && (g_mincolor >> 16) + 30 <= 255)
		g_mincolor = g_mincolor + (30 << 16);
	if (key == 17 && (g_mincolor >> 16) - 30 >= 0)
		g_mincolor = g_mincolor - (30 << 16);
	if (key == 5 && (g_mincolor >> 8) % 256 + 30 <= 255)
		g_mincolor = g_mincolor + (30 << 8);
	if (key == 4 && (g_mincolor >> 8) % 256 - 30 >= 0)
		g_mincolor = g_mincolor - (30 << 8);
	if (key == 11 && g_mincolor % 256 % 256 + 30 <= 255)
		g_mincolor = g_mincolor + 30;
	if (key == 45 && g_mincolor % 256 % 256 - 30 >= 0)
		g_mincolor = g_mincolor - 30;
	return (0);
}

int		numline(int fd)
{
	char	*line;
	int		i;

	g_mincolor = (50 << 8) + 100;
	g_maxcolor = (170 << 16) + (255 << 8) + 230;
	i = 0;
	while (ft_gnl(fd, &line) == 1)
		i++;
	close(fd);
	return (i - 1);
}

void	getinput(int fd, char *str)
{
	char *line;
	char **tmp;

	g_mh = numline(fd) + 1;
	g_in = (int**)malloc(sizeof(int*) * g_mh);
	g_s = (int**)malloc(sizeof(int*) * g_mh);
	fd = open(str, O_RDONLY);
	g_c.y = g_mh - 1;
	while (ft_gnl(fd, &line))
	{
		tmp = ft_strsplit(line, ' ');
		g_in[g_c.y] = (int*)malloc(sizeof(int) * ft_strlen(line));
		g_s[g_c.y] = (int*)malloc(sizeof(int) * ft_strlen(line));
		g_c.x = -1;
		while (tmp[++g_c.x])
		{
			g_in[g_c.y][g_c.x] = ft_atoi(tmp[g_c.x]);
			g_e.x = (g_e.x > g_in[g_c.y][g_c.x] ? g_in[g_c.y][g_c.x] : g_e.x);
			g_e.y = (g_e.y < g_in[g_c.y][g_c.x] ? g_in[g_c.y][g_c.x] : g_e.y);
		}
		g_c.y--;
	}
	close(fd);
	g_mw = g_c.x;
}

void	scaleheight(int n)
{
	float h;

	h = 1;
	if (g_e.y - g_e.x > 0)
		h = g_e.y - g_e.x;
	g_c.y = -1;
	while (++g_c.y < g_mh)
	{
		g_c.x = -1;
		while (++g_c.x < g_mw)
		{
			g_s[g_c.y][g_c.x] = n * (g_in[g_c.y][g_c.x] - g_e.x) / h;
		}
	}
}

int		free_and_exit(void)
{
	g_c.y = -1;
	while (++g_c.y < g_mh)
	{
		free(g_in[g_c.y]);
		free(g_s[g_c.y]);
	}
	free(g_in);
	free(g_s);
	exit(1);
}
