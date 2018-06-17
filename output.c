/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 01:01:22 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/16 01:01:23 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		num_roads(t_road **roads)
{
	int i;

	i = 0;
	while (roads[i])
		i++;
	return (i);
}

void	make_road(t_list **t, t_road **r, t_road **r2)
{
	if (!(*t)->pv || (*t)->head->room != (*t)->pv->head->room)
	{
		if ((*t)->pv)
			*r = (t_road*)malloc(sizeof(t_road));
		(*r)->room = (*t)->head->room;
		(*r)->pv = *r2;
		if (*r2)
			(*r2)->nx = *r;
		*r2 = *r;
	}
	(*t) = (*t)->nx;
}

t_road	**paths_to_roads(t_list **paths)
{
	int		i;
	t_list	*t;
	t_road	**roads;
	t_road	*r;
	t_road	*r2;

	i = 0;
	while (paths[i]->head)
		i = i + 1;
	roads = (t_road**)malloc(sizeof(t_road*) * (i + 1));
	i = -1;
	while (paths[++i]->head)
	{
		roads[i] = (t_road*)malloc(sizeof(t_road));
		r = roads[i];
		r2 = NULL;
		t = paths[i];
		while (t)
			make_road(&t, &r, &r2);
		r->nx = NULL;
	}
	roads[i] = NULL;
	return (roads);
}

t_ant	*assign_ants(t_road **roads, int *app, int ants)
{
	t_ant	*a;
	int		n_roads;
	int		c;
	int		st;
	int		i;

	a = (t_ant*)malloc(sizeof(t_ant) * (ants + 1));
	a[ants].st = -1;
	n_roads = num_roads(roads);
	c = 0;
	st = 0;
	i = 0;
	while (i < ants)
	{
		if (app[c] > 0)
		{
			a[i].p = roads[c];
			a[i].st = (a[i].p->nx->nx ? st : 0);
			a[i].print = 0;
			app[c]--;
			i++;
		}
		(c == n_roads - 1 && (c = 0) == 0 ? st++ : c++);
	}
	return (a);
}
