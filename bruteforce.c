/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bruteforce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:54:55 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/30 22:48:41 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

bool	check_cols_for_duplicates(t_map *map)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (i < map->size)
	{
		j = 0;
		while (j < map->size)
		{
			k = j;
			while (++k < map->size)
				if (map->map[i + k * map->size].value \
					== map->map[i + j * map->size].value)
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

bool	check_rows_for_duplicates(t_map *map)
{
	int		i;
	int		j;
	int		k;

	j = 0;
	while (j < map->size)
	{
		i = 0;
		while (i < map->size)
		{
			k = i;
			while (++k < map->size)
				if (map->map[j * map->size + k].value \
					== map->map[j * map->size + i].value)
					return (1);
			i++;
		}
		j++;
	}
	return (0);
}

bool	there_are_duplicates(t_map *map)
{
	return (check_cols_for_duplicates(map) | check_rows_for_duplicates(map));
}

bool	simple_bruteforce(t_map *map, t_uf8 pos)
{
	if (pos < (map->size * map->size - 1))
	{
		map->map[pos].value = 1;
		while (map->map[pos].value <= map->size)
		{
			simple_bruteforce(map, pos + 1);
			map->map[pos].value += 1;
		}
	}
	else
	{
		map->map[pos].value = 1;
		while (map->map[pos].value <= map->size)
		{
			if (is_solved(map))
			{
				print_board(map->map, map->size);
				return (0);
			}
			map->map[pos].value += 1;
		}
		return (1);
	}
	return (0);
}
