#include "rush01.h"

int	*get_views(int *views)
{
	static int	*static_views;

	if (!static_views)
		static_views = views;
	else if (views)
		views = static_views;
	return (views);
}

int	*init_views(int *views)
{
	get_views(views);
	return (views);
}

int	init(int *board, int *views, char *const *argv)
{
	int		i;

	views = malloc(4 * g_size * sizeof(int));
	if (!views)
		return (MALLOC_OOPSIE);
	board = malloc(g_size * g_size * sizeof(int));
	if (!board)
		return (MALLOC_OOPSIE);
	i = 0;
	while (i < g_size * 4)
	{
		views[i] = (argv[2 * i] - '0');
		i++;
	}
	init_views(views);
	i = 0;
	while (i < g_size * g_size)
	{
		board[i] = 0;
		i++;
	}
	return (0);
}
