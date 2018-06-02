/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 18:44:27 by cwu               #+#    #+#             */
/*   Updated: 2018/05/05 18:45:04 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	redraw(void)
{
	mlx_clear_window(g_mp, g_wp);
	g_c.y = g_mh;
	while (--g_c.y >= 0)
	{
		g_c.x = g_mw;
		while (--g_c.x >= 0)
		{
			if (g_c.y != g_mh - 1)
				connect(g_c.x, g_c.y, g_c.x, g_c.y + 1);
			if (g_c.x != g_mw - 1)
				connect(g_c.x, g_c.y, g_c.x + 1, g_c.y);
		}
	}
	return (0);
}

int	k_control(int key)
{
	if (key == 53)
		free_and_exit();
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
	else
		return (0);
	redraw();
	return (0);
}

int	m_control(int button)
{
	if (button == 5)
		g_sc++;
	if (button == 4 && g_sc > 0)
		g_sc--;
	if (button == 6)
	{
		if ((g_mincolor >> 16) > 5)
			g_mincolor -= 256 * 256 * 5;
		if ((g_mincolor >> 8 & 255) > 5)
			g_mincolor -= 256 * 5;
		if ((g_mincolor & 255) > 5)
			g_mincolor -= 5;
	}
	if (button == 7)
	{
		if ((g_mincolor >> 16) < 250)
			g_mincolor += 256 * 256 * 5;
		if ((g_mincolor >> 8 & 255) < 250)
			g_mincolor += 256 * 5;
		if ((g_mincolor & 255) < 250)
			g_mincolor += 5;
	}
	return (0);
}

int	motion(int x, int y)
{
	g_ang = 3.14 * (x - 750) / 1500;
	g_height = (int)(((float)600 - y) / 600 * 250);
	scaleheight(g_height);
	redraw();
	return (0);
}

int	main(int ac, char **av)
{
	int fd;

	if (ac != 2 || (fd = open(av[1], O_RDONLY)) == -1)
		return (-1);
	getinput(fd, av[1]);
	g_height = 150;
	scaleheight(g_height);
	g_mp = mlx_init();
	g_wp = mlx_new_window(g_mp, 1500, 1200, "Fdf");
	g_sc = (int)fmin(800 / g_mw, 500 / g_mh);
	redraw();
	mlx_key_hook(g_wp, &k_control, (void*)0);
	mlx_expose_hook(g_wp, &redraw, (void*)0);
	mlx_hook(g_wp, 6, 0, &motion, (void*)0);
	mlx_mouse_hook(g_wp, &m_control, (void*)0);
	mlx_loop(g_mp);
	return (0);
}
