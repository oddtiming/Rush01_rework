#include "rush01.h"

// working on this next!
int	set_next_value(t_rush01 *s, int x, int y)
{
	int	next_value;
	
	next_value = s->board[at(x, y)];
	if (next_value == 0)
		next_value = largest_bit(s->poss_vals[at(x, y)]);
	while ((s->poss_vals[at(x, y)] & (1 << next_value)) == 0)
	{
		if (next_value > g_size)
		{
			s->board[at(x, y)] = 0;
			break;
		}
		next_value--;
	}
	s->board[at(x, y)] = next_value;
	return (s->board[at(x, y)]);
}

int	L_search(t_rush01 *s, int x, int y, int (*f)(t_rush01 *, int, int))
{
	int	status;

	if (x == g_size - 1 && y == g_size - 1)
		return (IS_SOLVED);
	else if (x >= y && x != g_size - 1)	//going right in row
		status = f(s, x + 1, y);
	else if (x >= y)					//finished row, go to col
		status = f(s, y, y + 1);
	else if (y == g_size - 1)			//finished col, go to center of next L-search
		status = f(s, x + 1, x + 1);
	else								//going down in col
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
	// while (set_next_value(s, x, y))
	while (++(s->board[pos]) <= g_size)
	{
		if (is_duplicate(s->board, x, y) || (check_views(s, x, y)))
			continue ;
		if (L_search(s, x, y, solver) == IS_SOLVED)
			return (IS_SOLVED);
	}
	return (UNSOLVABLE);
}
