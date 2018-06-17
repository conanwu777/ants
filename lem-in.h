/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:46:30 by cwu               #+#    #+#             */
/*   Updated: 2018/06/13 17:46:31 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"

typedef struct	s_room t_room;
typedef struct	s_node t_node;
typedef struct	s_list t_list;
typedef struct	s_road t_road;
typedef struct	s_ant t_ant;

typedef struct	s_node
{
	t_node		**nodes;
	int			nc;
	t_room		*room;
	int			id;
	bool		visited;
}				t_node;

typedef struct	s_pt
{
	int			x;
	int			y;
}				t_pt;

typedef struct	s_room
{
	char		*name;
	t_pt		coor;
	t_room		**rooms;
	t_node		*in;
	t_node		*out;
	int			nc;
}				t_room;

typedef struct	s_nwk
{
	t_room		**r;
	t_room		*st;
	t_room		*end;
	int			nr;
}				t_nwk;

typedef struct	s_list
{
	t_node		*head;
	t_list		*nx;
	t_list		*pv;
}				t_list;

typedef struct	s_ant
{
	int			st;
	t_road		*p;
	bool		print;
}				t_ant;

typedef struct	s_road
{
	t_room		*room;
	t_road		*nx;
	t_road		*pv;
}				t_road;

typedef	struct	s_sym
{
	char		key;
	char		*value;
}				t_sym;

typedef	struct	s_pl
{
	t_pt		p;
	char		c;
}				t_pl;

void			reset_nodes_visited(t_nwk nwk);
void			*free_lvl(t_node **lvl);
int				get_level_connections(t_node **lvl);
bool			read_farm(t_nwk *nwk, int* ants);
void			extend_path(t_list **pp, t_node *node);
void			find_paths(t_nwk nwk, t_list **paths);
int				resolve_paths(t_list **paths);
int				start_search(t_nwk nwk, t_list **pp, t_node *target);
int				num_connect(t_node *node);
void    		nwk_setup(t_nwk *nwk);
void			update_nwk(t_list *path);
int				number(char **sp);
char			*name(char **sp, char c);
t_room			**realloc_rooms(t_room** old, int num);
bool			is_connected(t_nwk *nwk, int a, int b);
t_road			**paths_to_roads(t_list **paths);
void			set_app(t_road **roads, int **app, int ants);
void			print_ants(t_road **roads, int *app, int ants);
int				num_roads(t_road **roads);
t_ant 			*assign_ants(t_road **roads, int *app, int ants);
int				error();

#endif
