/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 03:40:41 by cwu               #+#    #+#             */
/*   Updated: 2018/06/15 03:40:43 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"
#include "display.h"

static t_sym	g_symbol[] =
{	{'-', "{GR}━━━"},
	{'|', "{GR} ┃ "},
	{'p', "{GR}━┓ "},
	{';', "{GR}━┛ "},
	{'l', "{GR} ┗━"},
	{'o', "{GR} ┏━"},
	{'r', "{GR}[ ]"},
	{'=', "{F}━━━"},
	{'1', "{F} ┃ "},
	{'P', "{F}━┓ "},
	{':', "{F}━┛ "},
	{'L', "{F} ┗━"},
	{'O', "{F} ┏━"},
	{'R', "{F}[ ]"},
	{'s', "{B}[S]"},
	{'e', "{R}[T]"},
	{'a', "{W}\e[1CⰛ\e[1C"},
	{'b', "{Y}\e[1CⰛ\e[1C"},
	{'c', "{O}\e[1CⰛ\e[1C"},
	{'d', "{A}\e[1CⰛ\e[1C"},
	{0, 0}
};

void	print_tab(char tab[H][W + 1])
{
	int i;
	int j;
	int k;

	i = -1;
	while (++i < g_dim.y)
	{
		j = -1;
		while (++j < g_dim.x)
		{
			k = -1;
			while (g_symbol[++k].key)
				if (g_symbol[k].key == tab[i][j])
				{
					ft_printf(g_symbol[k].value);
					break ;
				}
			if (!g_symbol[k].key)
				ft_printf("   ");
		}
		ft_printf("\n");
	}
}

void	print_frame(int n)
{
	char	tab[H][W + 1];
	int		i;
	int		j;

	i = -1;
	while (++i < g_dim.y)
	{
		j = -1;
		while (++j < g_dim.x)
			tab[i][j] = g_graph[i][j];
		tab[i][j] = '\0';
	}
	i = -1;
	while (g_a[++i].st != -1)
		if (g_a[i].print && g_a[i].p->nx)
			put_ant(tab, i, n);
	print_tab(tab);
}

int		animate(int c, int ants)
{
	int step;
	int i;

	step = 0;
	while (g_arr < ants)
	{
		i = -1;
		while (++i < ants)
		{
			if (g_a[i].st < step && g_a[i].print)
				g_a[i].p = g_a[i].p->nx;
			g_a[i].print = (g_a[i].st == step ? 1 : g_a[i].print);
		}
		i = -1;
		while (++i < c)
		{
			print_frame(i);
			ft_printf("{W}Ants Arrived: %d    Steps: %d\n", g_arr, step + 1);
			usleep(50000);
			ft_printf("\e[%dA", g_dim.y + 1);
		}
		usleep(100000);
		step++;
	}
	return (step);
}

void	display(t_nwk nwk, t_road **roads, int *app, int ants)
{
	int		c;
	int		step;

	g_arr = 0;
	if (!set_dim(nwk))
		return ;
	draw_roads(nwk, roads);
	g_a = assign_ants(roads, app, ants);
	ft_printf("\n");
	c = max_step(roads) + 1;
	step = animate(c, ants);
	print_frame(c);
	ft_printf("{W}ALL ANTS ARRIVED!!! Total steps: %d\n\n", step);
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
	paths = (t_list**)malloc(sizeof(t_list*) * nwk.nr);
	app = (int*)malloc(sizeof(int) * nwk.nr);
	find_paths(nwk, paths);
	if (paths[0]->head == NULL)
		return (error("{O}No Possible Path\n"));
	(void)roads;
	roads = paths_to_roads(paths);
	set_app(roads, &app, ants);
	display(nwk, roads, app, ants);
	return (0);
}
