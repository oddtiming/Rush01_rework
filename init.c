#include "rush01.h"

/**
 * Parsing is done here
 */
static int	set_g_size(int argc, char *argv[])
{
	int		nb_views;
	char	biggest_entry;
	int		i;

	if (argc != 2 || !is_digit(argv[1][0]))
		return (EXIT_FAILURE);
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
	g_size = nb_views / 4;
	if (!is_digit(argv[1][i - 1]) || nb_views % 4 || biggest_entry > g_size)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init(t_rush01 *s, int argc, char **argv)
{
	int	i;
	
	if (set_g_size(argc, argv))
		return (EXIT_FAILURE);
	
	s->bit_mask = ((ft_exp(2, g_size) - 1) << 1);
	
	s->board = ft_calloc(g_size * g_size * sizeof(int));
	if (!s->board)
		return err_msg("Malloc Error\n");
	
	s->poss_vals = ft_calloc(g_size * g_size * sizeof(int));
	if (!s->poss_vals)
		return err_msg("Malloc Error\n");

	s->views = malloc(4 * g_size * sizeof(int));
	if (!s->views)
		return err_msg("Malloc Error\n");
	i = 0;
	while (i < g_size * 4)
	{
		s->views[i] = (argv[1][2 * i] - '0');
		i++;
	}
	return (EXIT_SUCCESS);
}
