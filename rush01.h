/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:21:55 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/04 11:10:45 by iyahoui-         ###   ########.fr       */
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
# define _VIEWS_MIN 4
# define VIEWS_OK 0
# define VIEWS_BAD 1
# define IS_SOLVED 1
# define BAD_SOLUTION 0
# define MALLOC_OOPSIE 1
# define FREE_BOARD 42

int	g_size;

//INITIALIZATION
int		get_map_size(int argc, char *argv[]);
int		*init(int *views, char *views_string);
int		*init_views(int *views);
int		init_possible_values_board(int *possible_values_board);

//CHECKER
int		*get_views(int *views);
bool	is_duplicate(int *board, int x, int y);

//SOLVING
int		solver_simple(int *views, int *board, int x, int y);
int		L_search(int *views, int *board, int x, int y);
int		solver(int *board, int x, int y);
int		set_next_value(int *board, int x, int y);
void	set_possible_values(int *board, int *possible_values, int x, int y);



//UTILS
int		ft_sqrt(int nb);
bool	is_digit(char c);
void	print_views(int *views);
bool	print_board(int *board);
int		ft_exp(int base, int e);
int		smallest_bit(int nb);
int		fill_n_bits(int value);

#endif