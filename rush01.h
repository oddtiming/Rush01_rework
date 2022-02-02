/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:21:55 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/02 02:05:46 by iyahoui-         ###   ########.fr       */
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
# define NO_SOLUTIONS 1
# define BAD_SOLUTION 1

typedef struct s_pos
{
	uid_t	value;
	bool	is_set;
}	t_pos;

typedef struct s_map
{
	t_pos	*board;
	uid_t	*views;
	uid_t	size;
}	t_map;

//INITIALIZATION
uid_t	get_map_size(int argc, char *const *argv);
bool	init_map(t_map *map, char *views);

//CHECKER
bool	is_solved(t_pos	*board, uid_t *views, uid_t	size);
bool	there_are_duplicates(t_map *map);
uid_t	top_view_count(t_map *map, uid_t pos);
uid_t	bottom_view_count(t_map *map, uid_t pos);
uid_t	left_view_count(t_map *map, uid_t pos);
uid_t	right_view_count(t_map *map, uid_t pos);

//SOLVING
void	set_known_values(t_map *map);
bool	simple_bruteforce(t_pos *board, uid_t *views, uid_t size, uid_t pos, uid_t value);
bool	solver(t_map *map, uid_t pos);

//UTILS
int		ft_sqrt(int nb);
bool	is_digit(char c);
void	print_views(uid_t *views, int map_size);
bool	print_board(t_pos *map, uid_t size);

//Need to update modify board integration

#endif