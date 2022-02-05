#include "rush01.h"

static void	place_top(int *board, int *views)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_size)
	{
		if (views[i + (0 * g_size)] == 1)
			board[i] = g_size;
		else if (views[i + (0 * g_size)] == g_size)
		{
			j = 0;
			while (++j <= g_size)
			{
				board[(j - 1) * g_size + i] = j;
			}
		}
		i++;
	}
	return ;
}

static void	place_bottom(int *board, int *views)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_size)
	{
		if (views[i + (1 * g_size)] == 1)
			board[(g_size - 1) * g_size + i] = g_size;
		else if (views[i + (1 * g_size)] == g_size)
		{
			j = 0;
			while (++j <= g_size)
				board[(g_size - j) * g_size + i] = j;
		}
		i++;
	}
	return ;
}

static void	place_left(int *board, int *views)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_size)
	{
		if (views[i + (2 * g_size)] == 1)
			board[i * g_size] = g_size;
		else if (views[i + (2 * g_size)] == g_size)
		{
			j = 0;
			while (++j <= g_size)
				board[i * g_size + (j - 1)] = j;
		}
		i++;
	}
	return ;
}

static void	place_right(int *board, int *views)
{
	int	i;
	int	j;

	i = 0;
	while (i < g_size)
	{
		if (views[i + (3 * g_size)] == 1)
			board[i * g_size + (g_size - 1)] = g_size;
		else if (views[i + (3 * g_size)] == g_size)
		{
			j = 0;
			while (++j <= g_size)
				board[i * g_size + (g_size - j)] = j;
		}
		i++;
	}
	return ;
}

void	set_known_values(int *board)
{
	int	*views;

	views = 0;
	views = get_views(views);
	if (!views)
		return ;
	place_top(board, views);
	place_bottom(board, views);
	place_left(board, views);
	place_right(board, views);
	return ;
}
