#include "rush01.h"

int	g_size;

void	test_possible_values(int *board)
{
	int	*possible_values = malloc(g_size * g_size * sizeof(int));

	for (int i = 0; i < g_size * g_size; i++)
		possible_values[i] = 0;
	for (int j = 0; j < g_size; ++j) {
		for (int i = 0; i < g_size; ++i) {
			set_possible_values_at(board, possible_values, i, j);
		}
	}
	print_possible_values(possible_values);
	free(possible_values);
	return ;
}

int	main(int argc, char *argv[])
{
	int	*board;
	int	*views;

	g_size = set_g_size(argc, argv);
	if (g_size <= 0)
		return (write(2, "Error\n", sizeof("Error\n")));
	board = malloc(g_size * g_size * sizeof(int));
	if (!board)
		return (write(2, "Malloc Error\n", sizeof("Malloc Error\n")));
	for (int i = 0; i < g_size * g_size; i++)
		board[i] = 0;

	views = malloc(4 * g_size * sizeof(int));
	if (!views)
		return (write(2, "Malloc Error\n", sizeof("Malloc Error\n")));	
	views = parse_views(views, argv[1]);
		
	set_known_values(board);
	test_possible_values(board);

	// if (solver_simple(board, 0, 0) == UNSOLVABLE_BOARD)
	//  	return (write(2, "Unsolvable\n", sizeof("Unsolvable\n")));
	// 	print_board(board);
	free (board);
	free(views);
	set_next_value(0, FREE_BOARD, 0);
	return (EXIT_SUCCESS);
}
