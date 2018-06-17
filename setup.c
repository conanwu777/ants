/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 16:49:10 by cwu               #+#    #+#             */
/*   Updated: 2018/06/13 16:49:13 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	link_nodes(t_nwk *nwk)
{
	int i;
	int c;

	i = -1;
	while (nwk->r[++i])
	{
		nwk->r[i]->out->nc = nwk->r[i]->nc + 1;
		nwk->r[i]->out->nodes = (t_node**)malloc(sizeof(t_node*)
		* (nwk->nr) * (2 + 1));
		nwk->r[i]->out->nodes[nwk->r[i]->out->nc] = NULL;
		nwk->r[i]->out->id = 100000 + i;
		nwk->r[i]->in->id = i;
	}
	i = -1;
	while (nwk->r[++i])
	{
		nwk->r[i]->out->nodes[0] = nwk->r[i]->in;
		c = 0;
		while (c < nwk->r[i]->nc)
		{
			nwk->r[i]->out->nodes[c + 1] = nwk->r[i]->rooms[c]->in;
			c++;
		}
	}
}

void	nwk_setup(t_nwk *nwk)
{
	int i;

	i = 0;
	while (nwk->r[i])
	{
		nwk->r[i]->in = (t_node*)malloc(sizeof(t_node));
		nwk->r[i]->out = (t_node*)malloc(sizeof(t_node));
		nwk->r[i]->in->room = nwk->r[i];
		nwk->r[i]->out->room = nwk->r[i];
		nwk->r[i]->in->nc = 1;
		nwk->r[i]->in->nodes = (t_node**)malloc(sizeof(t_node*) *
		(nwk->nr) * (2 + 1));
		nwk->r[i]->in->nodes[0] = nwk->r[i]->out;
		nwk->r[i]->in->nodes[1] = NULL;
		i++;
	}
	link_nodes(nwk);
}

void	update_nwk(t_list *path)
{
	int		i;
	t_list	*t;

	t = path;
	while (t->nx && t->nx->head)
	{
		i = 0;
		while (t->head->nodes[i] != t->nx->head)
			i++;
		while (t->head->nodes[i + 1])
		{
			t->head->nodes[i] = t->head->nodes[i + 1];
			i++;
		}
		t->head->nodes[i] = NULL;
		i = t->nx->head->nc;
		t->nx->head->nodes[i] = t->head;
		t->nx->head->nodes[i + 1] = NULL;
		t = t->nx;
	}
}

int		num_connect(t_node *node)
{
	int num;

	num = 0;
	while (node->nodes[num])
		num++;
	return (num);
}
