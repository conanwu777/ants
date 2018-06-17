/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 00:33:56 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/16 00:33:58 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		road_length(t_road *r)
{
	int i;

	i = 0;
	while (r)
	{
		r = r->nx;
		i++;
	}
	return (i);
}

int		avg_road_length(t_road **roads, int *num_roads)
{
	int total;

	*num_roads = 0;
	total = 0;
	while (roads[*num_roads])
	{
		total += road_length(roads[*num_roads]);
		(*num_roads)++;
	}
	if (*num_roads == 0)
		return (0);
	return ((int)((float)total / *num_roads + 0.99999));
}

void	short_path(int **app, int i, int ants, t_road **roads)
{
	int c;

	c = 0;
	while (c < num_roads(roads))
	{
		app[0][c] = 0;
		c++;
	}
	app[0][i] = ants;
}

void	set_app(t_road **roads, int **app, int ants)
{
	int i;
	int avg;
	int ants_added;
	int num_roads;

	ants_added = 0;
	avg = avg_road_length(roads, &num_roads);
	i = -1;
	while (roads[++i])
	{
		if (road_length(roads[i]) <= 2)
			return (short_path(app, i, ants, roads));
		app[0][i] = (int)(ants / (float)num_roads + 0.99999)
		- road_length(roads[i]) + avg;
		if (app[0][i] > 0)
			ants_added += app[0][i];
	}
	i = 0;
	while (ants_added > ants)
	{
		i = (roads[i] ? i : 0);
		if (app[i] > 0 && (ants_added--) >= -1)
			app[0][i]--;
		i++;
	}
}
