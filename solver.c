#include "rush01.h"


//// work on this next!!!!
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
	// if (!board[x + y * g_size])
	// 	set_possible_values_at(board, possible_values, x, y);
	// else
		possible_values[x + y * g_size] &= ~(1 << board[x + y * g_size]);
	next_value = smallest_bit(possible_values[x + y * g_size]);
	board[x + y * g_size] = next_value;
	return (board[x + y * g_size]);
}

int	L_search(t_rush01 *s, int x, int y, int (*f)(t_rush01 *, int, int))
{
	int	status;

	if (x == g_size - 1 && y == g_size - 1)
		return (IS_SOLVED);
	else if ((x == y || x > y) && x != g_size - 1)	//going right in row
		status = f(s, x + 1, y);
	else if (x == y || x > y)	//finished row, go to col
		status = f(s, y, y + 1);
	else if (y == g_size - 1)	//finished col, go to center of next L-search
		status = f(s, x + 1, x + 1);
	else	//going down in col
		status = f(s, x, y + 1);
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
int	solver(t_rush01 *s, int x, int y)
{
	int	pos;
	
	pos = at(x, y);
	s->board[pos] = 0;
	while (++(s->board[pos]) <= g_size)
	{
		if (is_duplicate(s->board, x, y))
			continue ;				
		else if (x == g_size - 1 || y == g_size - 1)
		{
			//only check at end of row or col, I think it's more efficient
			if (check_views(s, x, y) == VIEWS_BAD)
				continue ;
		}
		if (L_search(s, x, y, solver) == IS_SOLVED)
				return (IS_SOLVED);
	}
	return (UNSOLVABLE);
}
