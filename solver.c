#include "rush01.h"

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
	if (!board[x + y * g_size])
		set_possible_values(board, possible_values, x, y);
	else
		possible_values[x + y * g_size] &= ~(1 << board[x + y * g_size]);
	next_value = smallest_bit(possible_values[x + y * g_size]);
	board[x + y * g_size] = next_value;
	return (board[x + y * g_size]);
}

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
	int	nb_visible;

	highest = board[x + y * g_size];
	nb_visible = 1;
	while (y-- > 0)
		if (board[x + y * g_size] > highest && nb_visible++)
			highest = board[x + y * g_size];
	if (nb_visible != views[1 * g_size + x])	//View for col-y-up
		return (VIEWS_BAD);
	y = 0;
	highest = board[x + y * g_size];
	nb_visible = 1;
	while (y++ < g_size - 1)
		if (board[x + y * g_size] > highest && nb_visible++)
			highest = board[x + y * g_size];
	if (nb_visible != views[0 * g_size + x])	//View for col-y-down
		return (VIEWS_BAD);
	return (VIEWS_OK);
}

int	check_row(int *views, int *board, int x, int y)
{
	int	highest;
	int	nb_visible;

	highest = board[x + y * g_size];
	nb_visible = 1;
	while (x-- > 0)
		if (board[x + y * g_size] > highest && nb_visible++)
			highest = board[x + y * g_size];
	if (nb_visible != views[3 * g_size + y])	//View for row-x-right
		return (VIEWS_BAD);
	x = 0;
	highest = board[x + y * g_size];
	nb_visible = 1;
	while (x++ < g_size - 1)
		if (board[x + y * g_size] > highest && nb_visible++)
			highest = board[x + y * g_size];
	if (nb_visible != views[2 * g_size + y])	//View for row-x-left
		return (VIEWS_BAD);
	return (VIEWS_OK);
}

int	check_views(int *board, int x, int y)
{
	int *views;

	views = NULL;
	views = get_views(views);
	if (x == g_size - 1 && check_row(views, board, x, y) == VIEWS_BAD)
		return (VIEWS_BAD);
	if (y == g_size - 1 && check_col(views, board, x, y) == VIEWS_BAD)
		return (VIEWS_BAD);
	return (VIEWS_OK);
}

int	L_search(int *board, int x, int y, int (*f)(int *, int, int))
{
	int	status;

	if (x == g_size - 1 && y == g_size - 1)
		return (IS_SOLVED);
	else if ((x == y || x > y) && x != g_size - 1)	//going right in row
		status = f(board, x + 1, y);
	else if (x == y || x > y)	//finished row, go to col
		status = f(board, y, y + 1);
	else if (y == g_size - 1)	//finished col, go to center of next L-search
		status = f(board, x + 1, x + 1);
	else	//going down in col
		status = f(board, x, y + 1);
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
int	solver_setknown(int *board, int x, int y)
{
	int		value;
	
	value = 0;
	if (board[x + y * g_size])
		return (L_search(board, x, y, solver_setknown));
	while (++value <= g_size)
	{
		board[x + y * g_size] = value;
		if (is_duplicate(board, x, y))
			continue ;				
		else if ((x == g_size - 1 || y == g_size - 1) && \
				check_views(board, x, y) == VIEWS_BAD)
			continue ;
		if (L_search(board, x, y, solver_setknown) == IS_SOLVED)
			return (IS_SOLVED);
	}
	return (UNSOLVABLE_BOARD);
}

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
		if (L_search(board, x, y, solver_simple) == IS_SOLVED)
				return (IS_SOLVED);
	}
	return (UNSOLVABLE_BOARD);
}