/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   known_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 18:00:35 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/02/02 02:38:43 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush01.h"

static void	place_top(t_map *map)
{
	uid_t	i;
	uid_t	j;

	i = 0;
	while (i < map->size)
	{
		if (map->views[i + (0 * map->size)] == 1)
		{
			map->board[i].value = map->size;
			map->board[i].is_set = true;
		}
		else if (map->views[i + (0 * map->size)] == map->size)
		{
			j = 0;
			while (++j <= map->size)
			{
				map->board[(j - 1) * map->size + i].value = j;
				map->board[(j - 1) * map->size + i].is_set = true;
			}
		}
		i++;
	}
	return ;
}

static void	place_bottom(t_map *map)
{
	uid_t	i;
	uid_t	j;

	i = 0;
	while (i < map->size)
	{
		if (map->views[i + (1 * map->size)] == 1)
		{
			map->board[(map->size - 1) * map->size + i].value = map->size;
			map->board[(map->size - 1) * map->size + i].is_set = true;
		}
		else if (map->views[i + (1 * map->size)] == map->size)
		{
			j = 0;
			while (++j <= map->size)
			{
				map->board[(map->size - j) * map->size + i].value = j;
				map->board[(map->size - j) * map->size + i].is_set = true;
			}
		}
		i++;
	}
	return ;
}

static void	place_left(t_map *map)
{
	uid_t	i;
	uid_t	j;

	i = 0;
	while (i < map->size)
	{
		if (map->views[i + (2 * map->size)] == 1)
		{
			map->board[i * map->size].value = map->size;
			map->board[i * map->size].is_set = true;
		}
		else if (map->views[i + (2 * map->size)] == map->size)
		{
			j = 0;
			while (++j <= map->size)
			{
				map->board[i * map->size + (j - 1)].value = j;
				map->board[i * map->size + (j - 1)].is_set = true;
			}
		}
		i++;
	}
	return ;
}

static void	place_right(t_map *map)
{
	uid_t	i;
	uid_t	j;

	i = 0;
	while (i < map->size)
	{
		if (map->views[i + (3 * map->size)] == 1)
		{
			map->board[i * map->size + (map->size - 1)].value = map->size;
			map->board[i * map->size + (map->size - 1)].is_set = true;
		}
		else if (map->views[i + (3 * map->size)] == map->size)
		{
			j = 0;
			while (++j <= map->size)
			{
				map->board[i * map->size + (map->size - j)].value = j;
				map->board[i * map->size + (map->size - j)].is_set = true;
			}
		}
		i++;
	}
	return ;
}

void	set_known_values(t_map *map)
{
	place_top(map);
	place_bottom(map);
	place_left(map);
	place_right(map);
	return ;
}
