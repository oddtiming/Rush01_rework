#include "rush01.h"

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

int	check_col(t_rush01 *s, int x, int y)
{
	int	highest;
	int	nb_visible;

	highest = s->board[at(x, y)];
	nb_visible = 1;
	while (y-- > 0)
		if (s->board[at(x, y)] > highest && nb_visible++)
			highest = s->board[at(x, y)];
	if (nb_visible != s->views[1 * g_size + x])	//View for col-y-up
		return (VIEWS_BAD);
	y = 0;
	highest = s->board[at(x, y)];
	nb_visible = 1;
	while (y++ < g_size - 1)
		if (s->board[at(x, y)] > highest && nb_visible++)
			highest = s->board[at(x, y)];
	if (nb_visible != s->views[0 * g_size + x])	//View for col-y-down
		return (VIEWS_BAD);
	return (VIEWS_OK);
}

int	check_row(t_rush01 *s, int x, int y)
{
	int	highest;
	int	nb_visible;

	highest = s->board[at(x, y)];
	nb_visible = 1;
	while (x-- > 0)
		if (s->board[at(x, y)] > highest && nb_visible++)
			highest = s->board[at(x, y)];
	if (nb_visible != s->views[3 * g_size + y])	//View for row-x-right
		return (VIEWS_BAD);
	x = 0;
	highest = s->board[at(x, y)];
	nb_visible = 1;
	while (x++ < g_size - 1)
		if (s->board[at(x, y)] > highest && nb_visible++)
			highest = s->board[at(x, y)];
	if (nb_visible != s->views[2 * g_size + y])	//View for row-x-left
		return (VIEWS_BAD);
	return (VIEWS_OK);
}

int	check_views(t_rush01 *s, int x, int y)
{
	if (x == g_size - 1 && check_row(s, x, y) == VIEWS_BAD)
		return (VIEWS_BAD);
	if (y == g_size - 1 && check_col(s, x, y) == VIEWS_BAD)
		return (VIEWS_BAD);
	return (VIEWS_OK);
}
