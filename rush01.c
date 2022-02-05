#include "rush01.h"

void	test_get_views(void)
{
	int	*views;

	views = get_views(views);
	print_views(views);
	return ;
}

/**
 * @brief Get the map size object. Will check whether the input is valid
 * 
 * @param argc 	to check that argc == 2
 * @param argv	to check that input is properly parsed
 * @return int	:	0 if the args are not valid, map_size otherwise
 */
int	get_map_size(int argc, char *argv[])
{
	int		nb_views;
	char	biggest_entry;
	int		i;

	if (argc != 2 || (*argv[1] && !is_digit(*argv[1])))
		return (0);
	i = 1;
	nb_views = 1;
	biggest_entry = 0;
	while (argv[1][i - 1] && argv[1][i])
	{
		if (!(argv[1][i] == ' ' && is_digit(argv[1][i - 1])))
			return (0);
		if (argv[1][i] > biggest_entry)
			biggest_entry = argv[1][i];
		nb_views += 1;
		i += 2;
	}
	if (!is_digit(argv[1][i - 1]) || nb_views % 4 || \
			biggest_entry - '0' > nb_views / 4)
		return (0);
	return (nb_views / 4);
}

int	main(int argc, char *argv[])
{
	int	*board;
	int	*views;

	g_size = get_map_size(argc, argv);
	if (g_size <= 0)
		return (write(2, "Error\n", sizeof("Error\n")));
	board = malloc(g_size * g_size * sizeof(int));
	if (!board)
		return (write(2, "Malloc Error\n", sizeof("Malloc Error\n")));
	views = malloc(4 * g_size * sizeof(int));
	if (!views)
		return (write(2, "Malloc Error\n", sizeof("Malloc Error\n")));
	
	views = parse_views(views, argv[1]);

	int i = 0;
	while (i < g_size * g_size)
	{
		board[i] = 0xff << i % 9;
		i++;
	}
	// board[0] = 0xf << 1;
	// board[0] &= ~(1 << 2);
	// board[0] &= ~(1 << 3);
	// board[1] &= (1 << 2);
	// board[2] &= (1 << 3);
	// board[3] &= (1 << 4);
	int *board_dimensions = calc_box_dimensions();
	printf("For g_size == %d, box dimensions are :\n", g_size);
	printf("width: %d\n", board_dimensions[0]);
	printf("height: %d\n", board_dimensions[1]);
	print_possible_values(board);
	free (board_dimensions);

	// set_known_values(board);

	// if (solver_setknown(board, 0, 0) == UNSOLVABLE_BOARD)
	//  	return (write(2, "Unsolvable\n", sizeof("Unsolvable\n")));
	// else
	// 	print_board(board);
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
 * - [x] Figure out how to know which direction to iterate
 * 
 */