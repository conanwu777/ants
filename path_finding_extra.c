/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 02:25:43 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/16 02:25:45 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		get_level_connections(t_node **lvl)
{
	int num;
	int c;

	num = 0;
	c = 0;
	while (lvl[c])
		num += num_connect(lvl[c++]);
	return (num);
}

void	*free_lvl(t_node **lvl)
{
	free(lvl);
	return (NULL);
}

void	reset_nodes_visited(t_nwk nwk)
{
	int count;

	count = 0;
	while (count < nwk.nr)
	{
		nwk.r[count]->in->visited = false;
		nwk.r[count]->out->visited = false;
		count++;
	}
}
