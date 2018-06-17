/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:01:45 by cwu               #+#    #+#             */
/*   Updated: 2018/06/13 17:01:46 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int		number(char **sp)
{
	int		i;
	int		nbr;
	char	*str;

	str = *sp;
	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i] && str[i] != ' ')
	{
		if (!isdigit(str[i]))
			return (INT_MIN + 17);
		i++;
	}
	i++;
	nbr = ft_atoi(str);
	*sp = cw_strchop(str, i);
	return (nbr);
}

char	*name(char **sp, char c)
{
	int		i;
	char	*str;
	char	*ret;

	str = *sp;
	if (str[0] == 'L')
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		if (!ft_isprint(str[i]))
			return (NULL);
		i++;
	}
	ret = ft_strnew(i);
	ft_strncpy(ret, str, i);
	i++;
	*sp = cw_strchop(str, i);
	return (ret);
}

t_room	**realloc_rooms(t_room **old, int num)
{
	t_room **rooms;
	t_room **tmp;
	t_room **old_tmp;

	rooms = (t_room**)malloc(sizeof(t_room*) * (num + 1));
	tmp = rooms;
	old_tmp = old;
	while (old && *old)
	{
		*tmp = *old;
		tmp++;
		old++;
	}
	rooms[num] = NULL;
	if (num != 1)
		free(old_tmp);
	return (rooms);
}

bool	is_connected(t_nwk *nwk, int a, int b)
{
	int i;

	i = 0;
	while (i < nwk->r[a]->nc)
	{
		if (nwk->r[a]->rooms[i]->name == nwk->r[b]->name)
			return (true);
		i++;
	}
	return (false);
}

int		error(char *str)
{
	write(1, "\e[H\e[0J", 7);
	ft_printf(str);
	return (0);
}
