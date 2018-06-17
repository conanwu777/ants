/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 14:23:35 by cwu               #+#    #+#             */
/*   Updated: 2018/06/16 14:23:40 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H
# include <math.h>

# define H 75
# define W 100

char	g_graph[H][W + 1];
t_pt	g_dim;
int		g_arr;
t_ant	*g_a;

void	h_road(char tab[H][W + 1], t_pt p1, t_pt p2, t_pt d);
void	v_road(char tab[H][W + 1], t_pt p1, t_pt p2, t_pt d);
void	draw_line(char tab[H][W + 1], t_pt p1, t_pt p2, int r);
void	draw_roads(t_nwk nwk, t_road **roads);
int		set_dim(t_nwk nwk);
void	put_ant(char tab[H][W + 1], int i, int n);
int		max_step(t_road **roads);
void	display(t_nwk nwk, t_road **roads, int *app, int ants);

#endif
