/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 02:10:07 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/16 02:10:09 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int g_iter;

t_node	*contains_node(t_node **lvl, t_node *target)
{
	int node;
	int connection;

	node = 0;
	while (lvl[node])
	{
		connection = 0;
		while (lvl[node]->nodes[connection])
		{
			if (lvl[node]->nodes[connection] == target)
				return (lvl[node]);
			connection++;
		}
		node++;
	}
	return (NULL);
}

t_node	**next_level(t_node **lvl)
{
	t_node	**nxt_lvl;
	int		node;
	int		connection;
	int		cur;
	int		total;

	total = 0;
	node = -1;
	cur = 0;
	nxt_lvl = (t_node**)malloc(sizeof(t_node*) *
	(get_level_connections(lvl) + 1));
	nxt_lvl[get_level_connections(lvl)] = NULL;
	while (lvl[++node])
	{
		connection = -1;
		while (lvl[node]->nodes[++connection])
		{
			nxt_lvl[total] = NULL;
			if (!lvl[node]->nodes[connection]->visited)
				nxt_lvl[cur++] = lvl[node]->nodes[connection];
			lvl[node]->nodes[connection]->visited = true;
			total++;
		}
	}
	return (nxt_lvl);
}

t_node	*shortest_path(t_nwk nwk, t_node **lvl, t_list **pp, t_node *target)
{
	t_node *backtrack;
	t_node *ret;
	t_node **nxt_lvl;

	if (g_iter > nwk.nr * 2)
		return (free_lvl(lvl));
	if ((ret = contains_node(lvl, target)) != NULL)
	{
		extend_path(pp, nwk.end->in);
		extend_path(pp, ret);
		free(lvl);
		return (ret);
	}
	nxt_lvl = next_level(lvl);
	g_iter++;
	backtrack = shortest_path(nwk, nxt_lvl, pp, target);
	if (!backtrack)
		return (free_lvl(lvl));
	ret = contains_node(lvl, backtrack);
	extend_path(pp, ret);
	free(lvl);
	return (ret);
}

int		start_search(t_nwk nwk, t_list **pp, t_node *target)
{
	t_node	**lvl0;
	t_list	*path;
	t_node	*ret;

	reset_nodes_visited(nwk);
	lvl0 = malloc(sizeof(t_node*) * 2);
	lvl0[0] = nwk.st->out;
	lvl0[1] = NULL;
	path = (t_list*)malloc(sizeof(t_list));
	path->head = NULL;
	g_iter = 0;
	ret = shortest_path(nwk, lvl0, &path, target);
	*pp = path;
	if (ret == NULL)
		return (-1);
	return (1);
}

void	find_paths(t_nwk nwk, t_list **paths)
{
	int num;

	num = 0;
	while (start_search(nwk, &(paths[num]), nwk.end->in) != -1)
	{
		update_nwk(paths[num]);
		num++;
	}
	while (resolve_paths(paths))
		;
}
