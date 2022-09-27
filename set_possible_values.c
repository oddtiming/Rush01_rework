#include "rush01.h"

/* 	removes values that don't satisfy the hints
 * 		example: if hint is 4, value at pos0 has to be smaller than g_size - 3
 */
void	remove_possible_values_at(t_rush01 *s, int x, int y)
{
	int	diff;
	int	pos;

	pos = at(x, y);
	diff = s->views[x + 0 * g_size] - (y + 1); // top views
	if (diff > 0)
		s->poss_vals[pos] &= (s->bit_mask >> (diff));
	diff = s->views[x + 1 * g_size] - (g_size - y); // bottom views
	if (diff > 0)
		s->poss_vals[pos] &= (s->bit_mask >> (diff));
	diff = s->views[y + 2 * g_size] - (x + 1); // left views
	if (diff > 0)
		s->poss_vals[pos] &= (s->bit_mask >> (diff));
	diff = s->views[y + 3 * g_size] - (g_size - x); // right views
	if (diff > 0)
		s->poss_vals[pos] &= (s->bit_mask >> (diff));
}

/* 	removes duplicates
 */
void	set_possible_values_at(t_rush01 *s, int x, int y)
{
	int			at_x;
	int			at_y;
	int			pos;

	at_x = g_size;
	at_y = g_size;
	pos = at(x, y);
	if (s->board[pos]) {
		s->poss_vals[pos] = 1 << s->board[pos];
		return ;
	}
	s->poss_vals[pos] = s->bit_mask;
	while (--at_x >= 0)
		s->poss_vals[pos] &= ~(1 << s->board[at(at_x, y)]);
	while (--at_y >= 0)
		s->poss_vals[pos] &= ~(1 << s->board[at(x, at_y)]);	
	remove_possible_values_at(s, x, y);
	return ;
}

void	set_possible_values(t_rush01 *s)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < g_size)
	{
		x = 0;
		while (x < g_size)
		{
			set_possible_values_at(s, x, y);
			x++;
		}
		y++;
	}
	return ;
}
