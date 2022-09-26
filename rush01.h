/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismaelyahyaouiracine <ismaelyahyaouirac    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:21:55 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/09/26 20:30:29 by ismaelyahya      ###   ########.fr       */
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
typedef enum e_return_values
{
	VIEWS_OK,
	VIEWS_BAD,
	IS_SOLVED,
	UNSOLVABLE_BOARD,
	MALLOC_OOPSIE,
	FREE_BOARD
}	t_return_values;

extern int	g_size;

typedef struct s_rush01
{
	int	*board;
	int	*views;
	int	*possible_values;
	int	bit_mask;
}	t_rush01;

/* init.c */
int		set_g_size(int argc, char *argv[]);
int		*parse_views(int *views, char *views_string);
int		*init_views(int *views);
void	set_known_values(int *board);
int		init_possible_values_board(int *possible_values_board);
bool	is_duplicate(int *board, int x, int y);

/* set_known_values.c */
void	set_known_values(int *board);

/* set_possible_values.c */
void	set_possible_values_at(int *board, int *possible_values, int x, int y);

/* Parsing */
int		*get_views(int *views);

/* solver.c */
int		solver_simple(int *board, int x, int y);
int		solver(int *board, int x, int y);
int		solver_setknown(int *board, int x, int y);
int		set_next_value(int *board, int x, int y);
void	set_possible_values(int *board, int *possible_values, int x, int y);

/* print_utils.c */
void	print_views(int *views);
int		print_board(int *board);
void	print_possible_values(int *possible_values);
int		*calc_box_dimensions(void);

/* utils.c */
bool	is_digit(char c);
int		ft_exp(int base, int e);
int		smallest_bit(int nb);
void	ft_putchar(int c);
int		at(int x, int y);
void	unset_bit(int *i, int b);
size_t	ft_strlen(char *s);

#endif