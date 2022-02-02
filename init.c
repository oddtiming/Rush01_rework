/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:21:59 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/02 02:39:02 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

bool	init_map(t_map *map, char *views)
{
	int		i;

	map->views = malloc(4 * map->size * sizeof(uid_t));
	if (!map->views)
		return (1);
	i = -1;
	while (++i < map->size * 4)
		map->views[i] = (views[2 * i] - '0');
	map->board = malloc(map->size * map->size * sizeof(t_pos));
	if (!map->board)
		return (1);
	i = 0;
	while (i < map->size * map->size)
	{
		map->board[i].value = 0;
		map->board[i].is_set = false;
		i++;
	}
	return (0);
}
