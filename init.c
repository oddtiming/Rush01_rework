#include "rush01.h"

// bool	parse_inputs()



/**
 * @brief Get the map size object. Will check whether the input is valid
 * 
 * @param argc 	to check that argc == 2
 * @param argv	to check that input is properly parsed
 * @return int	:	0 if the args are not valid, map_size otherwise
 */
int	set_g_size(int argc, char *argv[])
{
	int		nb_views;
	char	biggest_entry;
	int		i;

	if (argc != 2 || !is_digit(argv[1][0]))
		return (0);
	i = 1;
	nb_views = 1;
	biggest_entry = 0;
	while (argv[1][i - 1] && argv[1][i])
	{
		if (!(argv[1][i] == ' ' && is_digit(argv[1][i - 1])))
			return (0);
		if (argv[1][i] > biggest_entry)
			biggest_entry = argv[1][i] - '0';
		nb_views += 1;
		i += 2;
	}
	if (!is_digit(argv[1][i - 1]) || nb_views % 4 || \
			biggest_entry > nb_views / 4)
		return (0);
	g_size = nb_views / 4;
	return (g_size);
}

int	*get_views(int *views)
{
	static int	*static_views;

	if (!static_views && views)
		static_views = views;
	return (static_views);
}

int	*parse_views(int *views, char *views_string)
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

int	*init_views(int *views)
{
	get_views(views);
	return (views);
}
