/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:22:01 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/01 19:47:33 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

/**
 * @brief Get the map size object. Will check whether the input is valid
 * 
 * @param argc 
 * @param argv		
 * @return t_uf8	:	0 if the args are not valid, map_size otherwise
 */
//need to add inputs_are_valid(argc, argv[1]) 
						// -->need to not access argv[1] if argc < 2
t_uf8	get_map_size(int argc, char *const *argv)
{
	t_uf8	nb_views;
	char	biggest;
	int		i;

	biggest = 0;
	if (argc != 2 || !is_digit(*(argv[1])))
		return (0);
	i = 1;
	nb_views = 1;
	while (argv[1][i])
	{
		if (is_digit(argv[1][i]) && argv[1][i - 1] == ' ')
		{
			if (argv[1][i] > biggest)
				biggest = argv[1][i];
			nb_views += 1;
		}
		else if (!(argv[1][i] == ' ' && is_digit(argv[1][i - 1])))
			return (0);
		i++;
	}
	if (nb_views < VIEWS_MIN || nb_views % 4 || biggest - '0' > nb_views / 4)
		return (0);
	return (nb_views / 4);
}

// print_views(map.views_key, map.size);
// simple_bruteforce(&map, 0);
// print_board(map.map, map.size);
int	main(int argc, char *const *argv)
{
	t_map	map;
	t_uf8	map_size;

	map_size = get_map_size(argc, argv);
	if (map_size == 0 || init_map(&map, argv[1]))
	{
		write(2, "Error\n", sizeof("Error\n"));
		return (EXIT_FAILURE);
	}
	modify_board(&map);
	map.size = map_size;
	place_known_values(&map);
	print_board(map.map, map_size);
	// if (solver(&map, 0) == 0)
	// 	print_board(map.map, map.size);
	// else
	// 	return (EXIT_FAILURE);
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