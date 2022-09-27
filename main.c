#include "rush01.h"

int	g_size;

int	main(int argc, char *argv[])
{
	t_rush01	*s;

	s = malloc(sizeof(t_rush01));
	if (!s)
		return (err_msg("Malloc Error\n"));
		
	if (init(s, argc, argv))
		return (EXIT_FAILURE);
		
	set_known_values(s);
	set_possible_values(s);
	print_possible_values(s);

	if (solver(s, 0, 0) == UNSOLVABLE)
		return (err_msg("Unsolvable\n"));

	print_board(s->board);

	free(s->board);
	free(s->views);
	free(s->poss_vals);
	free(s);
	return (EXIT_SUCCESS);
}
