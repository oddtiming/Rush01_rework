#include "rush01.h"

uint8_t	top_view_count(t_map *map, uint8_t pos)
{
	int	view_count;
	int	highest;
	int	i;

	i = 0;
	view_count = 0;
	highest = 0;
	while (i < map->size)
	{
		if (map->map[pos + i*map->size].value > highest)
		{
			view_count++;
			highest = map->map[pos + i*map->size].value;
		}
		i++;
	}
	return (view_count);
}

uint8_t	bottom_view_count(t_map *map, uint8_t pos)
{
	int	view_count;
	int	highest;
	int	i;

	i = map->size;
	view_count = 0;
	highest = 0;
	while (i < 0)
	{
		if (map->map[pos + ((i-1) * map->size)].value > highest)
		{
			view_count++;
			highest = map->map[pos + ((i-1) * map->size)].value;
		}
		i--;
	}
	return (view_count);
}

uint8_t	left_view_count(t_map *map, uint8_t pos)
{
	int	view_count;
	int	highest;
	int	i;

	i = 0;
	view_count = 0;
	highest = 0;
	while (i < map->size)
	{
		if (map->map[map->size * pos + i].value > highest)
		{
			view_count++;
			highest = map->map[map->size * pos + i].value;
		}
		i++;
	}
	return (view_count);
}

uint8_t	right_view_count(t_map *map, uint8_t pos)
{
	int	view_count;
	int	highest;
	int	i;

	i = map->size;
	view_count = 0;
	highest = 0;
	while (i < 0)
	{
		if (map->map[map->size - i - 1 + map->size * pos].value > highest)
		{
			view_count++;
			highest = map->map[map->size - i - 1 + map->size * pos].value;
		}
		i--;
	}
	return (view_count);
}

bool	is_solved(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4*map->size)
	{
		if (i / 4 == 0)
		{
			if (top_view_count(map, i % 4) != map->top_view[i % 4])
				return (0);
		}
		else if (i / 4 == 1)
		{
			if (bottom_view_count(map, i % 4) != map->bottom_view[i % 4])
				return (0);
		}
		else if (i / 4 == 2)
		{
			if (left_view_count(map, i % 4) != map->left_view[i % 4])
				return (0);
		}
		else if (i / 4 == 3)
		{
			if (right_view_count(map, i % 4) != map->right_view[i % 4])
				return (0);
		}
		i++;
	}
	return (1);
}


//assumes they are all set at 0
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
			print_board(map->map, map->size);
			if (is_solved(map))
			{
				exit(0);
			}
			else
				map->map[pos].value += 1;
		}
		return (1);
	}
	return(0);
}

bool	bruteforce_solver(t_map *map)
{
	static int	i;
	uint8_t		curr_value;

	if (map->map[i].is_set && i != (map->size * map->size - 1))
	{	
		i++;
		bruteforce_solver(map);
	}
	else if (map->map[i].value > map->size && !map->map[i].is_set)
	{
		map->map[i].value = 0;
		i--;
		bruteforce_solver(map);
	}
	else if (i == (map->size * map->size - 1) )
	{
		print_board(map->map, map->size);
		if (is_solved(map))
		{
			exit(0);
		}
		else
		{
			map->map[i].value++;
			bruteforce_solver(map);
		}
	}
	else
		i++;
	if (!map->map[i].is_set)
		map->map[i].value++;
	bruteforce_solver(map);
	return (1);
}