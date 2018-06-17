/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_ants.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:40:53 by cwu               #+#    #+#             */
/*   Updated: 2018/06/15 03:40:55 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "display.h"

void	put_ant_h(char tab[H][W + 1], int i, int n)
{
	t_pt d;
	t_pt p1;
	t_pt p2;

	p1 = g_a[i].p->room->coor;
	p2 = g_a[i].p->nx->room->coor;
	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	if (n < abs(d.x) / 2)
		tab[p1.y][p1.x + (d.x >= 0 ? n : -n)] = 'a' + i % 4;
	else if (n - abs(d.x) / 2 <= abs(d.y))
		tab[p1.y + (d.y >= 0 ? 1 : -1) * (n - abs(d.x) / 2)]
	[(p1.x + p2.x) / 2] = 'a' + i % 4;
	else if (n < abs(d.x) + abs(d.y))
		tab[p2.y][p2.x + (d.x >= 0 ? -1 : 1)
			* (abs(d.x) + abs(d.y) - n)] = 'a' + i % 4;
	else
	{
		if (!g_a[i].p->nx->nx && n == abs(d.x) + abs(d.y))
		{
			g_a[i].print = 0;
			g_arr++;
		}
		tab[p2.y][p2.x] = 'a' + i % 4;
	}
}

void	put_ant_v(char tab[H][W + 1], int i, int n)
{
	t_pt d;
	t_pt p1;
	t_pt p2;

	p1 = g_a[i].p->room->coor;
	p2 = g_a[i].p->nx->room->coor;
	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	if (n < abs(d.y) / 2)
		tab[p1.y + (d.y >= 0 ? n : -n)][p1.x] = 'a' + i % 4;
	else if (n - abs(d.y) / 2 <= abs(d.x))
		tab[(p1.y + p2.y) / 2]
	[p1.x + (d.x >= 0 ? 1 : -1) * (n - abs(d.y) / 2)] = 'a' + i % 4;
	else if (n < abs(d.x) + abs(d.y))
		tab[p2.y + (d.y >= 0 ? -1 : 1)
			* (abs(d.x) + abs(d.y) - n)][p2.x] = 'a' + i % 4;
	else
	{
		if (!g_a[i].p->nx->nx && n == abs(d.x) + abs(d.y))
		{
			g_a[i].print = 0;
			g_arr++;
		}
		tab[p2.y][p2.x] = 'a' + i % 4;
	}
}

void	put_ant(char tab[H][W + 1], int i, int n)
{
	t_pt d;
	t_pt p1;
	t_pt p2;

	p1 = g_a[i].p->room->coor;
	p2 = g_a[i].p->nx->room->coor;
	d.x = p2.x - p1.x;
	d.y = p2.y - p1.y;
	if (abs(d.x) >= abs(d.y))
		put_ant_h(tab, i, n);
	else
		put_ant_v(tab, i, n);
}

int		max_step(t_road **roads)
{
	int		max;
	int		i;
	t_pt	d;
	t_road	*t;

	max = 0;
	i = 0;
	while ((t = roads[i]))
	{
		while (t->nx)
		{
			d.x = t->room->coor.x - t->nx->room->coor.x;
			d.y = t->room->coor.y - t->nx->room->coor.y;
			if (max < abs(d.x) + abs(d.y))
				max = abs(d.x) + abs(d.y);
			t = t->nx;
		}
		i++;
	}
	return (max);
}
