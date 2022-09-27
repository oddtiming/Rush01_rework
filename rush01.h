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
	UNSOLVABLE,
	MALLOC_OOPSIE,
	FREE_BOARD
}	t_return_values;

extern int	g_size;

typedef struct s_rush01
{
	int	*board;
	int	*views;
	int	*poss_vals;
	int	bit_mask;
}	t_rush01;

/* init.c */
int	init(t_rush01 *s, int argc, char **argv);

/* set_known_values.c */
void	set_known_values(t_rush01 *s);

/* set_possible_values.c */
void	set_possible_values(t_rush01 *s);

/* solver.c */
int		check_views(t_rush01 *s, int x, int y);

/* solver.c */
bool	is_duplicate(int *board, int x, int y);
int		solver(t_rush01 *s, int x, int y);
int		solver_setknown(int *board, int x, int y);
int		set_next_value(int *board, int x, int y);

/* print_utils.c */
void	print_views(int *views);
int		print_board(int *board);
void	print_possible_values(t_rush01 *s);
int		print_poss_vals_raw(int *board);
int		*calc_box_dimensions(void);

/* utils.c */
bool	is_digit(char c);
int		ft_exp(int base, int e);
int		smallest_bit(int nb);
void	ft_putchar(int c);
int		at(int x, int y);
void	unset_bit(int *i, int b);
size_t	ft_strlen(char *s);
int		err_msg(char *msg);
void	*ft_calloc(size_t sz);

#endif	// RUSH01_H