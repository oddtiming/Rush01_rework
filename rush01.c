#include "rush01.h"


/**
 * @brief Get the map size object. Will check whether the input is valid
 * 
 * @param argc 	to check that argc == 2
 * @param argv	to check that input is properly parsed
 * @return int	:	0 if the args are not valid, map_size otherwise
 */
int	get_map_size(int argc, char *argv[])
{
	int	nb_views;
	char	biggest_number;
	int		i;

	if (argc != 2 || (*argv[1] && !is_digit(*argv[1])))
		return (0);
	i = 1;
	nb_views = 1;
	biggest_number = 0;
	while (argv[1][i - 1] && argv[1][i])
	{
		if (!(argv[1][i] == ' ' && is_digit(argv[1][i - 1])))
			return (0);
		if (argv[1][i] > biggest_number)
			biggest_number = argv[1][i];
		nb_views += 1;
		i += 2;
	}
	if (!is_digit(argv[1][i - 1]) || nb_views < _VIEWS_MIN || \
			nb_views % 4 || biggest_number - '0' > nb_views / 4)
		return (0);
	return (nb_views / 4);
}

// print_views(map.views_key, map.size);
// simple_bruteforce(&map, 0);
// print_board(map.map, map.size);
int	main(int argc, char *argv[])
{
	int	*board;
	int	*views;

	g_size = get_map_size(argc, argv);
	if (g_size <= 0)
	{
		write(2, "Error\n", sizeof("Error\n"));
		return (EXIT_FAILURE);
	}
	// if (init(&board, &views, argv[1]))
	board = malloc(g_size * g_size * sizeof(int));
	if (!board)
	{
		write(2, "Malloc Error\n", sizeof("Malloc Error\n"));
		return (EXIT_FAILURE);
	}
	views = malloc(4 * g_size * sizeof(int));
	if (!views)
	{
		write(2, "Malloc Error\n", sizeof("Malloc Error\n"));
		return (EXIT_FAILURE);
	}
	views = init(views, argv[1]);
	// print_board(board);
	if (solver_simple(views, board, 0, 0) == BAD_SOLUTION)
	{
	 	write(2, "map failure\n", sizeof("map failure\n"));
	 	return (EXIT_FAILURE);
	}
	else
		print_board(board);
	free (board);
	free(views);
	set_next_value(0, FREE_BOARD, 0);
	return (EXIT_SUCCESS);
}
/**
 * @brief ideas:
 * 	- it's better to separate big functions into subfunction
 * 	that contain only the necessary elements.
 * 		
 * 	- typedef some variables for clarity to replace t_uf8
 * to determine the next value for a given cell:
 *	if (!map->map[pos].is_set) {
	 	//the fct below will assign 0 if it's bigger than size
 * 		map->map[pos].value = next_possible_value(map->, pos);
 *	}
	if (!map->maps[pos].value)
		return (1);
 * 		
 * 
 * 
 */
/**
 * Tired af, but I started some of the logic for set_net_pos
 * - [ ] Figure out how to know which direction to iterate
 * 
 */