/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:21:55 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/05 13:48:08 by iyahoui-         ###   ########.fr       */
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
# define VIEWS_OK 1
# define VIEWS_BAD 2
# define IS_SOLVED 3
# define UNSOLVABLE_BOARD 5
# define MALLOC_OOPSIE 6
# define FREE_BOARD 42

int	g_size;

//INITIALIZATION
int		get_map_size(int argc, char *argv[]);
int		*parse_views(int *views, char *views_string);
int		*init_views(int *views);
void	set_known_values(int *board);
int		init_possible_values_board(int *possible_values_board);

//CHECKER
int		*get_views(int *views);
bool	is_duplicate(int *board, int x, int y);

//SOLVING
int		L_search_compact(int *board, int x, int y);
int		solver_simple(int *board, int x, int y);
int		L_search(int *views, int *board, int x, int y);
int		solver(int *board, int x, int y);
int		solver_setknown(int *board, int x, int y);

int		set_next_value(int *board, int x, int y);
void	set_possible_values(int *board, int *possible_values, int x, int y);

//PRINTING
void	print_views(int *views);
int		print_board(int *board);
void	print_possible_values(int *possible_values);
int		*calc_box_dimensions(void);

//UTILS
int		ft_sqrt(int nb);
bool	is_digit(char c);
int		ft_exp(int base, int e);
int		smallest_bit(int nb);
int		fill_n_bits(int value);
void	ft_putchar(int c);

#endif