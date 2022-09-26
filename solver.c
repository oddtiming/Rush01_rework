#include "rush01.h"

int	init_possible_values_board(int *possible_values_board)
{
	int	i;
	
	possible_values_board = malloc(g_size * g_size * sizeof(int));
	if (!possible_values_board)
	{
		return (MALLOC_OOPSIE);
	}
	i = 0;
	while (i < g_size * g_size)
	{
		possible_values_board[i] = 0;
		i++;
	}
	return (0);
}

void	remove_possible_values(int *possible_values, int x, int y, int bit_mask)
{
	static int	*views;
	int			diff;

	if (!views)
		views = get_views(NULL);

	diff = views[x + 0 * g_size] - y;
	if (diff > 0) // Remove values for top views
		possible_values[x + y * g_size] &= (bit_mask >> (g_size - diff));
	diff = views[x + 1 * g_size] - (g_size - 1 - y);
	if (diff > 0) // Remove values for top views
		possible_values[x + y * g_size] &= (bit_mask >> (g_size - diff));
	diff = views[y + 2 * g_size] - x;
	if (diff > 0) // Remove values for top views
		possible_values[x + y * g_size] &= (bit_mask >> (g_size - diff));
	diff = views[y + 3 * g_size] - (g_size - 1 - x);
	if (diff > 0) // Remove values for top views
		possible_values[x + y * g_size] &= (bit_mask >> (g_size - diff));
}

//removes duplicates
void	set_possible_values(int *board, int *possible_values, int x, int y)
{
	static int	bit_mask;
	int			at_x;
	int			at_y;

	if (!bit_mask)
		bit_mask = ((ft_exp(2, g_size) - 1) << 1);
	at_x = x;
	at_y = y;
	possible_values[x + y * g_size] = bit_mask;
	while (--at_x >= 0)
		possible_values[x + y * g_size] &= ~(1 << board[at_x + y * g_size]);
	while (--at_y >= 0)
		possible_values[x + y * g_size] &= ~(1 << board[x + at_y * g_size]);	

	remove_possible_values(possible_values, x, y, bit_mask);
	return ;
}

int	set_next_value(int *board, int x, int y)
{
	static int	*possible_values;
	int			next_value;
	
	if (!possible_values)
	{
		possible_values = malloc(g_size * g_size * sizeof(int));
		if (!possible_values)
			return (MALLOC_OOPSIE);
	}
	if (x == FREE_BOARD || y == FREE_BOARD)
	{
		free(possible_values);
		possible_values = NULL;
		return (0);
	}
	// if (!possible_values[x + y * g_size])
	if (!board[x + y * g_size])
		set_possible_values(board, possible_values, x, y);
	else
		possible_values[x + y * g_size] &= ~(1 << board[x + y * g_size]);
	next_value = smallest_bit(possible_values[x + y * g_size]);
	// if (!next_value)
	// {
	// 	// if (views_are_valid(board, x, y)) //NEED TO CODE PARTIAL check_col
	// 	// 	break ;
	// 	next_value = smallest_bit(possible_values[x + y * g_size]);
	// }
	board[x + y * g_size] = next_value;
	return (board[x + y * g_size]);
}

int	solver(int *board, int x, int y)
{
	int		status;
	
	while (set_next_value(board, x, y))
	{
		if (x == g_size - 1 && y == g_size - 1)
		{
			return (IS_SOLVED);

		}
		else if ((x == y || x > y) && x != g_size - 1)	//going right in row
			status = solver(board, x + 1, y);
		else if (x == y || x > y)	//finished row, go down col
			status = solver(board, y + 1, y);
		else if (y == g_size - 1)	//finished col, go center of next L-search
			status = solver(board, x + 1, x + 1);
		else	//going down in col
			status = solver(board, x, y + 1);
		if (status == IS_SOLVED)
			return (IS_SOLVED);
	}
	return (UNSOLVABLE_BOARD);
}
	//for solver
	// if ((x + 1) * (y + 1) == g_size * g_size && board[x + y * g_size] != 0)
	// 	return (IS_SOLVED);
	// else if ((x + 1) * (y + 1) == g_size * g_size)
	// 	break;

bool	is_duplicate(int *board, int x, int y)
{
	int	at_x;
	int	at_y;
	int curr_value;
	
	at_x = x;
	at_y = y;
	curr_value = board[x + y * g_size];
	while (--at_x >= 0)
		if (board[at_x + y * g_size] == curr_value)
			return (true);
	while (--at_y >= 0)
		if (board[x + at_y * g_size] == curr_value)
			return (true);
	return (false);
}

int	check_col(int *views, int *board, int x, int y)
{
	int	highest;
	int	nb_views;

	highest = board[x + y * g_size];
	nb_views = 1;
	while (y-- > 0)
		if (board[x + y * g_size] > highest && nb_views++)
			highest = board[x + y * g_size];
	if (nb_views != views[1 * g_size + x])	//View for col-y-up
		return (VIEWS_BAD);
	y = 0;
	highest = board[x + y * g_size];
	nb_views = 1;
	while (y++ < g_size - 1)
		if (board[x + y * g_size] > highest && nb_views++)
			highest = board[x + y * g_size];
	if (nb_views != views[0 * g_size + x])	//View for col-y-down
		return (VIEWS_BAD);
	return (VIEWS_OK);
}

int	check_row(int *views, int *board, int x, int y)
{
	int	highest;
	int	nb_views;

	highest = board[x + y * g_size];
	nb_views = 1;
	while (x-- > 0)
		if (board[x + y * g_size] > highest && nb_views++)
			highest = board[x + y * g_size];
	if (nb_views != views[3 * g_size + y])	//View for row-x-right
		return (VIEWS_BAD);
	x = 0;
	highest = board[x + y * g_size];
	nb_views = 1;
	while (x++ < g_size - 1)
		if (board[x + y * g_size] > highest && nb_views++)
			highest = board[x + y * g_size];
	if (nb_views != views[2 * g_size + y])	//View for row-x-left
		return (VIEWS_BAD);
	return (VIEWS_OK);
}

int	check_views(int *board, int x, int y)
{
	int *views;

	views = get_views(views);
	if (x == g_size - 1 && check_row(views, board, x, y) == VIEWS_BAD)
		return (VIEWS_BAD);
	if (y == g_size - 1 && check_col(views, board, x, y) == VIEWS_BAD)
		return (VIEWS_BAD);
	return (VIEWS_OK);
}

int	L_search_expanded(int *board, int x, int y)
{
	int	next_x;
	int	next_y;

	next_x = x;
	next_y = y;
	if (x == g_size - 1 && y == g_size - 1)
		return (IS_SOLVED);
	else if ((x == y || x > y) && x != g_size - 1)	//going right in row
		next_x++;
	else if (x == y || x > y)	//finished row, go to col
	{
		next_x = y;
		next_y++;
	}
	else if (y == g_size - 1)	//finished col, go to center of next L-search
	{
		next_y = x + 1;
		next_x++;
	}
	else	//going down in col
		next_y++;
	if (solver_simple(board, next_x, next_y) == IS_SOLVED)
		return (IS_SOLVED);
	return (UNSOLVABLE_BOARD);
}

int	L_search_cleaner(int *board, int x, int y)
{
	int	next_x;
	int	next_y;

	next_x = x;
	next_y = y;
	if (x == g_size - 1 && y == g_size - 1)
		return (IS_SOLVED);
	else if ((x == y || x > y) && x == g_size - 1)	//finished row, go to col
		next_x = y;
	else if ((x == y || x > y) || y == g_size - 1)	//going right in row
		next_x++;
	if (y > x && y == g_size - 1)	//finished col, go to center of next L-search
		next_y = x + 1;
	else if (y > x || x == g_size - 1)	//going down in col
		next_y++;
	if (solver_simple(board, next_x, next_y) == IS_SOLVED)
		return (IS_SOLVED);
	return (UNSOLVABLE_BOARD);
}

int	L_search_compact(int *board, int x, int y)
{
	int	status;

	if (x == g_size - 1 && y == g_size - 1)
		return (IS_SOLVED);
	else if ((x == y || x > y) && x != g_size - 1)	//going right in row
		status = solver_simple(board, x + 1, y);
	else if (x == y || x > y)	//finished row, go to col
		status = solver_simple(board, y, y + 1);
	else if (y == g_size - 1)	//finished col, go to center of next L-search
		status = solver_simple(board, x + 1, x + 1);
	else	//going down in col
		status = solver_simple(board, x, y + 1);
	return (status);
}

// |--------<---- Program start
// v
// |--->-----> |++value <= size?| --No--> return (BAD_SOLN)
// |                |           ^
// ^               Yes           \
// |                v             \
// |-<--Yes---|is duplicate?|      \
// |                |               \
// |               No                \
// |                v                 \
// |        |end of row or col?|--No-->try_next_pos
// |                |                    ^
// |               Yes                  No
// |                v                    |
// |-<--No-----|VIEWS_OK?|-->-Yes-->|is last_pos?|--Yes--> return (IS_SOLVED)
int	solver_simple(int *board, int x, int y)
{
	board[x + y * g_size] = 0;
	while (++board[x + y * g_size] <= g_size)
	{
		// if (is_duplicate(board, x, y) || check_views(board, x, y) == VIEWS_BAD)
		// 	continue ;				
		if (is_duplicate(board, x, y))
			continue ;				
		else if (x == g_size - 1 || y == g_size - 1)
		{
			//only check at end of row or col, I think it's more efficient
			if (check_views(board, x, y) == VIEWS_BAD)
				continue ;
		}
		if (L_search_compact(board, x, y) == IS_SOLVED)
				return (IS_SOLVED);
	}
	return (UNSOLVABLE_BOARD);
}

int	solver_setknown(int *board, int x, int y)
{
	int		value;
	bool	is_set;
	
	value = 0;
	is_set = false;
	if (board[x + y * g_size])
		return (L_search_compact(board, x, y));
	while (++value <= g_size)
	{
		board[x + y * g_size] = value;
		if (is_duplicate(board, x, y))
			continue ;				
		else if ((x == g_size - 1 || y == g_size - 1) && \
				check_views(board, x, y) == VIEWS_BAD)
			continue ;
		if (L_search_compact(board, x, y) == IS_SOLVED)
			return (IS_SOLVED);
	}
	return (UNSOLVABLE_BOARD);
}
