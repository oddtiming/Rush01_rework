/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 14:21:59 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/01 00:48:48 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

bool	init_map(t_map *map, char *views)
{
	int		i;

	map->views_key = malloc(4 * map->size);
	if (!map->views_key)
		return (1);
	i = -1;
	while (++i < map->size * 4)
		map->views_key[i] = (views[2 * i] - '0');
	map->top_view = &map->views_key[0 * map->size];
	map->bottom_view = &map->views_key[1 * map->size];
	map->left_view = &map->views_key[2 * map->size];
	map->right_view = &map->views_key[3 * map->size];
	map->map = malloc(map->size * map->size * sizeof(t_pos));
	if (!map->map)
		return (1);
	i = 0;
	while (i < map->size * map->size)
	{
		map->map[i].value = 0;
		map->map[i].is_set = false;
		i++;
	}
	return (0);
}
