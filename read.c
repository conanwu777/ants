/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 16:51:25 by cwu               #+#    #+#             */
/*   Updated: 2018/06/13 16:51:28 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

bool	make_link(t_nwk *nwk, char *str, char *line)
{
	t_pt	link;

	link.x = -1;
	while (++link.x < nwk->nr && ft_strcmp(nwk->r[link.x]->name, str) != 0)
		;
	link.y = -1;
	while (++link.y < nwk->nr && ft_strcmp(nwk->r[link.y]->name, line) != 0)
		;
	if (link.x == nwk->nr || link.y == nwk->nr)
		return (false);
	if (!is_connected(nwk, link.x, link.y))
	{
		nwk->r[link.x]->nc++;
		nwk->r[link.y]->nc++;
		nwk->r[link.x]->rooms =
		realloc_rooms(nwk->r[link.x]->rooms, nwk->r[link.x]->nc);
		nwk->r[link.y]->rooms =
		realloc_rooms(nwk->r[link.y]->rooms, nwk->r[link.y]->nc);
		nwk->r[link.x]->rooms[nwk->r[link.x]->nc - 1] = nwk->r[link.y];
		nwk->r[link.y]->rooms[nwk->r[link.y]->nc - 1] = nwk->r[link.x];
	}
	return (true);
}

bool	read_connections(t_nwk *nwk, char *line)
{
	bool	first;
	char	*str;
	int		wc;

	first = true;
	while (first == true || (ft_gnl(0, &line) &&
		((wc = cw_countw(line, '-')) == 2 || line[0] == '#')))
	{
		first = false;
		if (*line == '#')
		{
			ft_printf("%s\n", line);
			free(line);
			continue ;
		}
		ft_printf("{Y}%s\n", line);
		str = name(&line, '-');
		if (!str || !make_link(nwk, str, line))
			return (false);
		free(str);
		free(line);
	}
	return (true);
}

bool	set_nwk(t_nwk *nwk, char **lp, t_pt *s_t)
{
	(s_t->x || s_t->y ? ft_printf("{R}%s\n", *lp) : ft_printf("{O}%s\n", *lp));
	nwk->nr++;
	nwk->r = realloc_rooms(nwk->r, nwk->nr);
	nwk->r[nwk->nr - 1] = (t_room*)malloc(sizeof(t_room));
	nwk->r[nwk->nr - 1]->nc = 0;
	nwk->r[nwk->nr - 1]->rooms = NULL;
	if (!(nwk->r[nwk->nr - 1]->name = name(lp, ' ')) ||
		(nwk->r[nwk->nr - 1]->coor.x = number(lp)) == INT_MIN + 17 ||
		(nwk->r[nwk->nr - 1]->coor.y = number(lp)) == INT_MIN + 17 ||
		(s_t->x && nwk->st) || (s_t->y && nwk->end))
		return (false);
	if (s_t->x)
	{
		nwk->st = nwk->r[nwk->nr - 1];
		s_t->x = 0;
	}
	if (s_t->y)
	{
		nwk->end = nwk->r[nwk->nr - 1];
		s_t->y = 0;
	}
	return (true);
}

bool	read_rooms(t_nwk *nwk)
{
	char	*line;
	int		wc;
	t_pt	s_t;

	s_t.x = 0;
	s_t.y = 0;
	while (ft_gnl(0, &line) == 1 &&
		((wc = cw_countw(line, ' ')) == 3 || line[0] == '#'))
	{
		if (*line == '#')
		{
			if (ft_strcmp(line, "##start") == 0 && (s_t.x = 1) > 0)
				ft_printf("{R}%s\n", line);
			else if (ft_strcmp(line, "##end") == 0 && (s_t.y = 1) > 0)
				ft_printf("{R}%s\n", line);
			else
				ft_printf("%s\n", line);
		}
		else if (!set_nwk(nwk, &line, &s_t))
			return (false);
		free(line);
	}
	if (wc == 1 && nwk->end && nwk->st)
		return (read_connections(nwk, line));
	return (false);
}

bool	read_farm(t_nwk *nwk, int *ants)
{
	char	*line;

	if (ft_gnl(0, &line) == 0)
		return (false);
	if ((*ants = number(&line)) < 0)
		return (false);
	ft_printf("{W}%d\n", *ants);
	free(line);
	nwk->r = NULL;
	nwk->st = NULL;
	nwk->end = NULL;
	nwk->nr = 0;
	if (!read_rooms(nwk))
		return (false);
	return (nwk->end != nwk->st);
}
