/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:21:55 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/30 23:00:34 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH01_H
# define RUSH01_H
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>

//TO REMOVE
# include <stdio.h>
//END OF REMOVE

//DEFINES
# define VIEWS_MIN 4

typedef uint_fast8_t	t_uf8;
typedef struct s_pos
{
	t_uf8	value;
	bool	is_set;
}	t_pos;

typedef struct s_map
{
	t_pos	*map;
	t_uf8	*views_key;
	t_uf8	*top_view;
	t_uf8	*bottom_view;
	t_uf8	*left_view;
	t_uf8	*right_view;
	t_uf8	size;
}	t_map;

//INITIALIZATION
t_uf8	get_map_size(int argc, char *const *argv);
bool	init_map(t_map *map, char *views);

//CHECKER
bool	is_solved(t_map *map);
bool	there_are_duplicates(t_map *map);
t_uf8	top_view_count(t_map *map, t_uf8 pos);
t_uf8	bottom_view_count(t_map *map, t_uf8 pos);
t_uf8	left_view_count(t_map *map, t_uf8 pos);
t_uf8	right_view_count(t_map *map, t_uf8 pos);

//SOLVING
void	place_known_values(t_map *map);
bool	simple_bruteforce(t_map *map, t_uf8 pos);
bool	solver(t_map *map, t_uf8 pos);

//UTILS
int		ft_sqrt(int nb);
bool	is_digit(char c);
void	print_views(t_uf8 *views, int map_size);
bool	print_board(t_pos *map, t_uf8 size);

#endif