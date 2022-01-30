/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:55:31 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/30 17:56:37 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

//This solver assumes known values have been placed
bool	solver(t_map *map, uint8_t pos)
{
	if (pos < (map->size * map->size - 1))
	{
		while (map->map[pos].is_set)
			pos++;
		map->map[pos].value = 1;
		while (map->map[pos].value <= map->size)
		{
			solver(map, pos + 1);
			map->map[pos].value += 1;
		}
	}
	else
	{
		map->map[pos].value = 1;
		while (map->map[pos].value <= map->size)
		{
			if (is_solved(map))
				return (print_board(map->map, map->size));
			map->map[pos].value += 1;
		}
		return (1);
	}
	return (0);
}
