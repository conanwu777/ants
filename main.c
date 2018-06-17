/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 02:16:34 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/16 02:16:36 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	print_ant(int i, int *arr, t_ant *a)
{
	if (i % 31 == 0)
		ft_printf("{R}L%d-%s ", i + 1, a[i].p->room->name);
	else if (i % 11 == 0)
		ft_printf("{Y}L%d-%s ", i + 1, a[i].p->room->name);
	else if (i % 7 == 0)
		ft_printf("{G}L%d-%s ", i + 1, a[i].p->room->name);
	else if (i % 5 == 0)
		ft_printf("{O}L%d-%s ", i + 1, a[i].p->room->name);
	else if (i % 3 == 0)
		ft_printf("{B}L%d-%s ", i + 1, a[i].p->room->name);
	else
	{
		settext(100, 100, 100);
		ft_printf("L%d-%s ", i + 1, a[i].p->room->name);
	}
	if (!a[i].p->nx)
	{
		a[i].print = 0;
		(*arr)++;
	}
	else
		a[i].p = a[i].p->nx;
}

void	print_ants(t_road **roads, int *app, int ants)
{
	int		i;
	int		step;
	int		arr;
	t_ant	*a;

	a = assign_ants(roads, app, ants);
	arr = 0;
	step = 0;
	while (arr < ants)
	{
		i = -1;
		while (++i < ants)
		{
			if (a[i].st < step && a[i].print)
				print_ant(i, &arr, a);
			if (a[i].st == step)
			{
				a[i].print = 1;
				a[i].p = a[i].p->nx;
			}
		}
		ft_printf("\n");
		step++;
	}
	free(a);
}

int		main(void)
{
	t_nwk	nwk;
	t_list	**paths;
	t_road	**roads;
	int		ants;
	int		*app;

	nwk.r = NULL;
	write(1, "\e[H\e[0J", 7);
	if (!read_farm(&nwk, &ants))
		return (error("{R}ERROR\n"));
	nwk_setup(&nwk);
	paths = (t_list **)malloc(sizeof(t_list *) * (nwk.nr + 1));
	app = (int *)malloc(sizeof(int) * nwk.nr);
	find_paths(nwk, paths);
	if (paths[0]->head == NULL)
		return (error("{O}No Possible Path\n"));
	roads = paths_to_roads(paths);
	set_app(roads, &app, ants);
	print_ants(roads, app, ants);
	return (0);
}
