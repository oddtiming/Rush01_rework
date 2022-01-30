/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_solved.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:55:26 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/01/30 17:59:14 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

// printf("top view count for x = %d = %d\n", curr_x, view_count);
uint8_t	top_view_count(t_map *map, uint8_t curr_x)
{
	int	view_count;
	int	highest;
	int	current_height;
	int	i;

	i = 0;
	view_count = 0;
	highest = 0;
	while (i < map->size)
	{
		current_height = map->map[curr_x + i * map->size].value;
		if (current_height > highest)
		{
			view_count++;
			highest = current_height;
		}
		i++;
	}
	return (view_count);
}

// printf("bottom view count for x = %d = %d\n", curr_x, view_count);
uint8_t	bottom_view_count(t_map *map, uint8_t curr_x)
{
	int	view_count;
	int	highest;
	int	current_height;
	int	i;

	i = map->size;
	view_count = 0;
	highest = 0;
	while (i > 0)
	{
		current_height = map->map[(i - 1) * map->size + curr_x].value;
		if (current_height > highest)
		{
			view_count++;
			highest = current_height;
		}
		i--;
	}
	return (view_count);
}

// printf("left view count for y = %d = %d\n", curr_y, view_count);
uint8_t	left_view_count(t_map *map, uint8_t curr_y)
{
	int	view_count;
	int	highest;
	int	current_height;
	int	i;

	i = 0;
	view_count = 0;
	highest = 0;
	while (i < map->size)
	{
		current_height = map->map[map->size * curr_y + i].value;
		if (current_height > highest)
		{
			view_count++;
			highest = current_height;
		}
		i++;
	}
	return (view_count);
}

// printf("right view count for y = %d = %d\n", curr_y, view_count);
uint8_t	right_view_count(t_map *map, uint8_t curr_y)
{
	int	view_count;
	int	highest;
	int	current_height;
	int	i;

	i = map->size;
	view_count = 0;
	highest = 0;
	while (i > 0)
	{
		current_height = map->map[i - 1 + map->size * curr_y].value;
		if (current_height > highest)
		{
			view_count++;
			highest = current_height;
		}
		i--;
	}
	return (view_count);
}

bool	is_solved(t_map *map)
{
	int	i;

	if (there_are_duplicates(map))
		return (0);
	i = 0;
	while (i < map->size)
	{
		if (top_view_count(map, i) != map->top_view[i] || \
			bottom_view_count(map, i) != map->bottom_view[i] || \
			left_view_count(map, i) != map->left_view[i] || \
			right_view_count(map, i) != map->right_view[i])
			return (0);
		i++;
	}
	return (1);
}
