/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:21:55 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/30 18:09:42 by iyahoui-         ###   ########.fr       */
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

typedef struct s_pos
{
	uint8_t	x;
	uint8_t	y;
	uint8_t	value;
	bool	is_set;
}	t_pos;

typedef struct s_map
{
	t_pos	*map;
	uint8_t	*views_key;
	uint8_t	*top_view;
	uint8_t	*bottom_view;
	uint8_t	*left_view;
	uint8_t	*right_view;
	uint8_t	size;
}	t_map;

//INITIALIZATION
uint8_t	get_map_size(int argc, char *const *argv);
bool	init_map(t_map *map, char *views);

//CHECKER
bool	is_solved(t_map *map);
bool	there_are_duplicates(t_map *map);
uint8_t	top_view_count(t_map *map, uint8_t pos);
uint8_t	bottom_view_count(t_map *map, uint8_t pos);
uint8_t	left_view_count(t_map *map, uint8_t pos);
uint8_t	right_view_count(t_map *map, uint8_t pos);

//SOLVING
void	place_known_values(t_map *map);
bool	simple_bruteforce(t_map *map, uint8_t pos);
bool	solver(t_map *map, uint8_t pos);

//UTILS
int		ft_sqrt(int nb);
bool	is_digit(char c);
void	print_views(uint8_t *views, int map_size);
bool	print_board(t_pos *map, uint8_t size);

#endif