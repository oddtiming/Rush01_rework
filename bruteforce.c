#include "rush01.h"

bool	there_are_duplicates(t_map *map)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	//CHECK COLUMNS
	while (i < map->size)
	{
		j = 0;
		while (j < map->size)
		{
			k = j;
			while (++k < map->size)
				if (map->map[i + k * map->size].value == map->map[i + j * map->size].value)
					return (1);
			j++;
		}
		i++;
	}
	j = 0;
	//CHECK COLUMNS
	while (j < map->size)
	{
		i = 0;
		while (i < map->size)
		{
			k = i;
			while (++k < map->size)
				if (map->map[j * map->size + k].value == map->map[j * map->size + i].value)
					return (1);
			i++;
		}
		j++;
	}
	return (0);
}

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
		current_height = map->map[curr_x + i*map->size].value;
		if (current_height > highest)
		{
			view_count++;
			highest = current_height;
		}
		i++;
	}
	// printf("top view count for x = %d = %d\n", curr_x, view_count);
	return (view_count);
}

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
		current_height = map->map[(i-1) * map->size + curr_x].value;
		if (current_height > highest)
		{
			view_count++;
			highest = current_height;
		}
		i--;
	}
	// printf("bottom view count for x = %d = %d\n", curr_x, view_count);
	return (view_count);
}

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
	// printf("left view count for y = %d = %d\n", curr_y, view_count);
	return (view_count);
}

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
	// printf("right view count for y = %d = %d\n", curr_y, view_count);
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
			bottom_view_count(map, i) != map->bottom_view[i]  || \
			left_view_count(map, i) != map->left_view[i]  || \
			right_view_count(map, i) != map->right_view[i])
			return (0);
		i++;
	}
	return (1);
}

bool	simple_bruteforce(t_map *map, uint8_t pos)
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
				// printf("board is solved!\n");
				return (0);
			}
			map->map[pos].value += 1;
		}
		return (1);
	}
	return(0);
}
