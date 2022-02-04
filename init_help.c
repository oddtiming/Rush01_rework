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

int	*init(int *views, char *views_string)
{
	int		i;

	i = 0;
	if (!views || !views_string)
		return (NULL);
	while (i < g_size * 4)
	{
		views[i] = (views_string[2 * i] - '0');
		i++;
	}
	init_views(views);
	return (views);
}
