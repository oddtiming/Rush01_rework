#include "rush01.h"

int	init_possible_values_board(int *possible_values_board)
{
	int	i;
	
	*possible_values_board = malloc(g_size * g_size * sizeof(int));
	if (!possible_values_board)
	{
		possible_values_board = NULL;
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

//removes duplicates
void	set_possible_values(int *board, int *possible_values, int x, int y)
{
	int	at_x;
	int	at_y;

	at_x = x;
	at_y = y;
	if (possible_values[x + y * g_size] == 0)
		possible_values[x + y * g_size] = (exp(2, g_size) - 1) << 1;
	while (--at_x >= 0)
		possible_values[x + y * g_size] &= ~(1 << board[at_x + y * g_size]);
	while (--at_y >= 0)
		possible_values[x + y * g_size] &= ~(1 << board[x + at_y * g_size]);
	return ;
}

int	set_next_value(int *board, int x, int y)
{
	static int	*possible_values;
	int			next_value;
	
	if (!possible_values)
		if (init_possible_values_board(possible_values) == MALLOC_OOPSIE)
			return (MALLOC_OOPSIE);
	if (x == FREE_BOARD || y == FREE_BOARD)
	{
		free(possible_values);
		possible_values = NULL;
		return (NULL);
	}
	if (!possible_values[x + y * g_size])
		set_possible_values(board, possible_values, x, y);
	next_value = smallest_bit(possible_values[x + y * g_size]);
	while (next_value)
	{
		if (views_are_valid(board, x, y))		//GOTTA CODE THIS
			break ;
		possible_values[x + y * g_size] &= ~(1 << next_value);
		next_value = smallest_bit(possible_values[x + y * g_size]);
	}
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
	return (BAD_SOLUTION);
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
	while (--at_x <= 0)
		if (board[at_x + y * g_size] == curr_value)
			return (true);
	while (--at_y <= 0)
		if (board[x + at_y * g_size] == curr_value)
			return (true);
	return (false);
}

int	solver_simple(int *views, int *board, int x, int y)
{
	int	status;
	
	board[x + y * g_size] = 0;
	while (++board[x + y * g_size] <= g_size)
	{
		if (((x == g_size - 1 || y == g_size - 1) && 
			check_views(views, board, x, y)) && !is_duplicate(board, x, y)) //NEED TO CODE check_views()
			break ;
		if (board[x + y * g_size] > g_size)
			return (BAD_SOLUTION);
		else if (x == g_size - 1 && y == g_size - 1)
			return (IS_SOLVED);
		else if ((x == y || x > y) && x != g_size - 1)	//going right in row
			status = solver(views, board, x + 1, y);
		else if (x == y || x > y)	//finished row, go down col
			status = solver(views, board, y + 1, y);
		else if (y == g_size - 1)	//finished col, go center of next L-search
			status = solver(views, board, x + 1, x + 1);
		else	//going down in col
			status = solver(views, board, x, y + 1);
		if (status == IS_SOLVED)
			return (IS_SOLVED);
	}
	return (BAD_SOLUTION);
}