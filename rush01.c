/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:22:01 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/30 11:01:33 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

/**
 * @brief Get the map size object. Will check whether the input is valid
 * 
 * @param argc 
 * @param argv		
 * @return uint8_t	:	0 if the args are not valid, map_size otherwise
 */
uint8_t	get_map_size(int argc, char *const *argv)
{
	uint8_t	nb_views;
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
		else if ( !(argv[1][i] == ' ' && is_digit(argv[1][i - 1])) )
			return (0);
		i++;
	}
	// printf("nb_views = %d\n", nb_views);
	if (nb_views < VIEWS_MIN || nb_views % 4 || biggest - '0' > nb_views / 4)
		return (0);
	return (nb_views / 4);
}

int	main(int argc, char *const *argv)
{
	t_map	map;
	uint8_t	map_size;

	map_size = get_map_size(argc, argv);
	map.size = map_size;
	if (map_size == 0)
		write(2, "Error\n", sizeof("Error\n"));
	
	init_map(&map, argv[1]);
	if (!map.views_key || !map.map)
		write(2, "Malloc Error\n", sizeof("Malloc Error\n"));

	print_views(map.views_key, map.size);
	print_4x4_board(map.map, map.size);

	if (place_known_values(&map))
		write(2, "known_values error\n", sizeof("known_values error\n"));

	printf("after place_known_values:\n");	
	print_4x4_board(map.map, map.size);
	return (0);
}