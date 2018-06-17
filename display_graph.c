/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_graph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:40:26 by cwu               #+#    #+#             */
/*   Updated: 2018/06/15 03:40:28 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "display.h"

void	h_line(char tab[H][W + 1], t_pt p1, t_pt p2, t_pt d)
{
	t_pt t;

	t.x = p1.x;
	t.y = p1.y;
	while (t.x < (p1.x + p2.x) / 2 && ++t.x != (p1.x + p2.x) / 2)
		tab[t.y][t.x] = '-';
	if (p2.y - p1.y >= 0)
		tab[t.y][t.x] = (d.y != 0 ? 'p' : '-');
	else
		tab[t.y][t.x] = (d.y != 0 ? ';' : '-');
	while (t.y != p2.y)
	{
		t.y += (p2.y - p1.y >= 0 ? 1 : -1);
		tab[t.y][t.x] = '|';
	}
	if (d.y > 0)
		tab[t.y][t.x] = 'l';
	if (d.y < 0)
		tab[t.y][t.x] = 'o';
	while (t.x < p2.x && ++t.x != p2.x)
		tab[t.y][t.x] = '-';
}

void	v_line(char tab[H][W + 1], t_pt p1, t_pt p2, t_pt d)
{
	t_pt t;

	t.x = p1.x;
	t.y = p1.y;
	while (t.y != (p1.y + p2.y) / 2)
	{
		tab[t.y][t.x] = '|';
		t.y += (p2.y >= p1.y ? 1 : -1);
	}
	if (p2.y >= p1.y)
		tab[t.y][t.x] = (d.x != 0 ? 'l' : '|');
	else
		tab[t.y][t.x] = (d.x != 0 ? 'o' : '|');
	if (d.x != 0)
	{
		while (++t.x < p2.x)
			tab[t.y][t.x] = '-';
		tab[t.y][t.x] = (d.y < 0 ? ';' : 'p');
	}
	t.y += (p2.y >= p1.y ? 1 : -1);
	while (t.y != p2.y)
	{
		tab[t.y][t.x] = '|';
		t.y += (p2.y >= p1.y ? 1 : -1);
	}
}

void	draw_line(char tab[H][W + 1], t_pt p1, t_pt p2, int r)
{
	t_pt d;
	t_pt tmp;

	d.x = p2.x - p1.x;
	if (d.x < 0)
	{
		tmp = p1;
		p1 = p2;
		p2 = tmp;
		d.x *= -1;
	}
	d.y = p2.y - p1.y;
	if (d.x >= abs(d.y) && r == 0)
		h_line(tab, p1, p2, d);
	else if (d.x >= abs(d.y) && r == 1)
		h_road(tab, p1, p2, d);
	else if (d.x < abs(d.y) && r == 0)
		v_line(tab, p1, p2, d);
	else
		v_road(tab, p1, p2, d);
}

void	set_graph(t_nwk nwk)
{
	t_pt p;
	t_pt c;

	p.y = -1;
	while (++p.y < H)
	{
		p.x = -1;
		while (++p.x < W)
			g_graph[p.y][p.x] = ' ';
		g_graph[p.y][p.x] = '\0';
	}
	c.x = -1;
	while (nwk.r[++c.x] && (c.y = -1) == -1)
		while (++c.y < nwk.r[c.x]->nc)
			if (nwk.r[c.x]->in->id <= nwk.r[c.x]->rooms[c.y]->in->id)
				draw_line(g_graph, nwk.r[c.x]->coor,
					nwk.r[c.x]->rooms[c.y]->coor, 0);
	c.x = -1;
	while (nwk.r[++c.x])
		g_graph[nwk.r[c.x]->coor.y][nwk.r[c.x]->coor.x] = 'r';
}

int		set_dim(t_nwk nwk)
{
	int i;

	g_dim.x = 0;
	g_dim.y = 0;
	i = -1;
	while (nwk.r[++i])
	{
		if (g_dim.x < nwk.r[i]->coor.x)
			g_dim.x = nwk.r[i]->coor.x;
		if (g_dim.y < nwk.r[i]->coor.y)
			g_dim.y = nwk.r[i]->coor.y;
	}
	g_dim.x++;
	g_dim.y += 2;
	if (g_dim.x > W || g_dim.y > H)
	{
		ft_printf("{W}\nCoordinates too large for screen\n");
		ft_printf("{W}(0 <= x <= %d) && (0 <= y <= %d)\n", W - 1, H - 2);
		return (0);
	}
	set_graph(nwk);
	return (1);
}
