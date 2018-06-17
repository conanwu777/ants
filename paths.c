/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 02:09:46 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/16 02:09:52 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	extend_path(t_list **pp, t_node *node)
{
	t_list *t;

	t = (t_list*)malloc(sizeof(t_list));
	t->head = node;
	if (!((*pp)->head))
	{
		free(*pp);
		t->nx = NULL;
	}
	else
		t->nx = *pp;
	t->pv = NULL;
	(*pp)->pv = t;
	*pp = t;
}

int		free_overlap(t_list *old_p2, t_list *p1, t_list *t2, t_list *t1)
{
	t_list *tmp;

	while (old_p2 != t2)
	{
		tmp = old_p2;
		old_p2 = old_p2->pv;
		free(tmp);
	}
	while (p1 != t1)
	{
		tmp = p1;
		p1 = p1->pv;
		free(tmp);
	}
	return (1);
}

void	find_second_overlap(t_list **p1, t_list **p2, t_list **t2)
{
	while ((*p1)->nx)
		(*p1) = (*p1)->nx;
	while ((*p2)->pv)
		(*p2) = (*p2)->pv;
	while ((*p1) && (*p1)->pv)
	{
		(*t2) = (*p2);
		while ((*t2)->nx->nx && (*t2)->head != (*p1)->head)
			(*t2) = (*t2)->nx;
		if ((*t2)->head == (*p1)->head)
			break ;
		(*p1) = (*p1)->pv;
	}
}

int		cancel_ovlp(t_list *p1, t_list *p2)
{
	t_list	*t1;
	t_list	*t2;
	t_list	*old_p2;
	bool	b;

	b = false;
	t1 = NULL;
	while (p2->nx)
		p2 = p2->nx;
	while (p2 && p2->pv && (t1 = p1) == p1)
	{
		while (t1->nx->nx && t1->head != p2->head)
			t1 = t1->nx;
		if (t1->head == p2->head && (b = true) == true)
			break ;
		p2 = p2->pv;
	}
	if ((old_p2 = p2) == p2 && !b)
		return (0);
	find_second_overlap(&p1, &p2, &t2);
	t1->nx = old_p2->nx;
	old_p2->nx->pv = t1;
	t2->nx = p1->nx;
	p1->nx->pv = t2;
	return (free_overlap(old_p2, p1, t2, t1));
}

int		resolve_paths(t_list **paths)
{
	int i;
	int j;
	int ovlp;

	ovlp = 0;
	i = 0;
	while (paths[i]->head)
	{
		j = i + 1;
		while (paths[j]->head)
		{
			ovlp += cancel_ovlp(paths[i], paths[j]);
			j++;
		}
		i++;
	}
	return (ovlp);
}
