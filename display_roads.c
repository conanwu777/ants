/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_roads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:17:16 by cwu               #+#    #+#             */
/*   Updated: 2018/06/15 16:17:18 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "display.h"

void	h_road(char tab[H][W + 1], t_pt p1, t_pt p2, t_pt d)
{
	t_pt t;

	t.x = p1.x;
	t.y = p1.y;
	while (t.x < (p1.x + p2.x) / 2 && ++t.x != (p1.x + p2.x) / 2)
		tab[t.y][t.x] = '=';
	if (p2.y - p1.y >= 0)
		tab[t.y][t.x] = (d.y != 0 ? 'P' : '=');
	else
		tab[t.y][t.x] = (d.y != 0 ? ':' : '=');
	while (t.y != p2.y)
	{
		t.y += (p2.y - p1.y >= 0 ? 1 : -1);
		tab[t.y][t.x] = '1';
	}
	if (d.y > 0)
		tab[t.y][t.x] = 'L';
	if (d.y < 0)
		tab[t.y][t.x] = 'O';
	while (t.x < p2.x && ++t.x != p2.x)
		tab[t.y][t.x] = '=';
}

void	v_road(char tab[H][W + 1], t_pt p1, t_pt p2, t_pt d)
{
	t_pt t;

	t.x = p1.x;
	t.y = p1.y;
	while (t.y != (p1.y + p2.y) / 2)
	{
		tab[t.y][t.x] = '1';
		t.y += (p2.y >= p1.y ? 1 : -1);
	}
	if (p2.y >= p1.y)
		tab[t.y][t.x] = (d.x != 0 ? 'L' : '1');
	else
		tab[t.y][t.x] = (d.x != 0 ? 'O' : '1');
	if (d.x != 0)
	{
		while (++t.x < p2.x)
			tab[t.y][t.x] = '=';
		tab[t.y][t.x] = (d.y < 0 ? ':' : 'P');
	}
	t.y += (p2.y >= p1.y ? 1 : -1);
	while (t.y != p2.y)
	{
		tab[t.y][t.x] = '1';
		t.y += (p2.y >= p1.y ? 1 : -1);
	}
}

void	draw_roads(t_nwk nwk, t_road **roads)
{
	int		i;
	t_pt	p1;
	t_pt	p2;
	t_road	*t;

	i = -1;
	while ((t = roads[++i]))
		while (t->nx)
		{
			p1 = t->room->coor;
			p2 = t->nx->room->coor;
			draw_line(g_graph, p1, p2, 1);
			t = t->nx;
		}
	i = -1;
	while ((t = roads[++i]))
		while (t)
		{
			g_graph[t->room->coor.y][t->room->coor.x] = 'R';
			t = t->nx;
		}
	g_graph[nwk.st->coor.y][nwk.st->coor.x] = 's';
	g_graph[nwk.end->coor.y][nwk.end->coor.x] = 'e';
}

t_pt	set_pt(int x, int y)
{
	t_pt p;

	p.x = x;
	p.y = y;
	return (p);
}
